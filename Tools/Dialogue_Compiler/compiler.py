import csv

NODES_FILE = 'Nodes.csv'
RESPONSES_FILE = 'Responses.csv'
OUTPUT_FILE = 'DT_Result.csv'

def compile_dialogue():
    responses_by_node = {}

    # Reading responses and grouping them by ParentNode
    with open(RESPONSES_FILE, mode='r', encoding='utf-8') as f:
        reader = csv.DictReader(f)
        for row in reader:
            parent = row['ParentNode']
            if parent not in responses_by_node:
                responses_by_node[parent] = []

            # Get category from CSV, default to 'Aggressive' if empty
            category = row.get('Category', 'Aggressive').strip()
            if not category:
                category = 'Aggressive'

            resp_str = (
                f'(Requirement_Response=,Set_By_Caller_Magnitude=('
                f'(Attribute_Tag=(TagName="Attribute.Player.Dominance"),Attribute_Magnitude={row["Dominance"]}),'
                f'(Attribute_Tag=(TagName="Attribute.Player.Empathy"),Attribute_Magnitude={row["Empathy"]}),'
                f'(Attribute_Tag=(TagName="Attribute.Player.Fatigued"),Attribute_Magnitude={row["Fatigued"]}),'
                f'(Attribute_Tag=(TagName="Attribute.Player.Sanity"),Attribute_Magnitude={row["Sanity"]})'
                f'),Text_Response=LOCTABLE("/TLGame/Data/ST_Dialogues_Inner_Voice.ST_Dialogues_Inner_Voice", "{row["Text_Response"]}"),'
                f'Row_ID_Next="{row["Next_Row"]}",Category={category})'
            )
            responses_by_node[parent].append(resp_str)

    # Processing nodes and injecting aggregated responses
    with open(NODES_FILE, mode='r', encoding='utf-8') as f_in, \
         open(OUTPUT_FILE, mode='w', encoding='utf-8', newline='') as f_out:

        reader = csv.DictReader(f_in)
        fieldnames = reader.fieldnames
        writer = csv.DictWriter(f_out, fieldnames=fieldnames)
        writer.writeheader()

        for row in reader:
            node_id = row['---']
            if node_id in responses_by_node:
                row['Player_Responses'] = '(' + ','.join(responses_by_node[node_id]) + ')'
            else:
                row['Player_Responses'] = '()'
            writer.writerow(row)

    print("Done! File created.")

if __name__ == '__main__':
    compile_dialogue()