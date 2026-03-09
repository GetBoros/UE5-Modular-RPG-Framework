import csv
import os

NODES_FILE = 'Nodes.csv'
RESPONSES_FILE = 'Responses.csv'
OUTPUT_FILE = 'DT_Result.csv'

# Точный путь к String Table в Unreal Engine
PATH_ST_DIALOGUES = "/TLGame/Data/Inner_Voice/ST_Dialogues_Inner_Voice.ST_Dialogues_Inner_Voice"

def compile_dialogue():
    # 1. Проверка наличия файлов (если ты перенес скрипт, но забыл CSV)
    if not os.path.exists(RESPONSES_FILE) or not os.path.exists(NODES_FILE):
        print(f"[ОШИБКА] Файлы {NODES_FILE} или {RESPONSES_FILE} не найдены в папке со скриптом!")
        return

    responses_by_node = {}

    # 2. Читаем ответы
    with open(RESPONSES_FILE, mode='r', encoding='utf-8') as f:
        reader = csv.DictReader(f)
        for row in reader:
            parent = row.get('ParentNode', '').strip()
            if not parent:
                continue # Пропускаем пустые строки

            if parent not in responses_by_node:
                responses_by_node[parent] =[]

            category = row.get('Category', 'Aggressive').strip() or 'Aggressive'

            # Формируем вложенный макрос для Unreal
            resp_str = (
                f'(Requirement_Response=,Set_By_Caller_Magnitude=('
                f'(Attribute_Tag=(TagName="Attribute.Player.Dominance"),Attribute_Magnitude={row.get("Dominance", 0)}.000000),'
                f'(Attribute_Tag=(TagName="Attribute.Player.Empathy"),Attribute_Magnitude={row.get("Empathy", 0)}.000000),'
                f'(Attribute_Tag=(TagName="Attribute.Player.Fatigued"),Attribute_Magnitude={row.get("Fatigued", 0)}.000000),'
                f'(Attribute_Tag=(TagName="Attribute.Player.Sanity"),Attribute_Magnitude={row.get("Sanity", 0)}.000000)'
                f'),Text_Response=LOCTABLE("{PATH_ST_DIALOGUES}", "{row.get("Text_Response", "")}"),'
                f'Row_ID_Next="{row.get("Next_Row", "")}",Category={category})'
            )
            responses_by_node[parent].append(resp_str)

    # 3. Читаем узлы и собираем финальный файл
    with open(NODES_FILE, mode='r', encoding='utf-8') as f_in, \
         open(OUTPUT_FILE, mode='w', encoding='utf-8', newline='') as f_out:

        reader = csv.DictReader(f_in)
        fieldnames = reader.fieldnames # ДИНАМИЧЕСКИЕ ЗАГОЛОВКИ (не сломается от новых колонок)

        if 'Player_Responses' not in fieldnames:
            fieldnames.append('Player_Responses')

        # extrasaction='ignore' защищает от крашей, если структура немного поехала
        writer = csv.DictWriter(f_out, fieldnames=fieldnames, quoting=csv.QUOTE_MINIMAL, extrasaction='ignore')
        writer.writeheader()

        # Определяем, как называется колонка ID (Unreal экспортирует '---', Google Sheets может 'RowName')
        id_col = '---' if '---' in fieldnames else 'RowName'

        for row in reader:
            node_id = row.get(id_col, '')

            # Вставляем собранные ответы
            if node_id in responses_by_node:
                row['Player_Responses'] = '(' + ','.join(responses_by_node[node_id]) + ')'
            else:
                row['Player_Responses'] = '()'

            writer.writerow(row)

    print("[УСПЕХ] Файл DT_Result.csv успешно сгенерирован!")

if __name__ == '__main__':
    compile_dialogue()