//------------------------------------------------------------------------------------------------------------
#include <Components/TLG_Component_Dialogue.h>

#include <System/TLG_HUD.h>
#include <System/TLG_Player_State.h>
#include <System/TLG_Game_State.h>

#include <Data/TLG_Data_Enemy.h>
#include <Data/TLG_Types.h>
//------------------------------------------------------------------------------------------------------------





// UTLG_Component_Dialogue
UTLG_Component_Dialogue::UTLG_Component_Dialogue()
{
	PrimaryComponentTick.bCanEverTick = false;

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Dialogue::BeginPlay()
{
	Super::BeginPlay();

    // 2.0. Check
    if (ensureMsgf(TLG_HUD, TEXT("Need HUD implemented from ATLG_HUD")) != true)
        return;

    if (ensureMsgf(TLG_Player_State, TEXT("Need Player State implemented from ATLG_Player_State")) != true)
        return;

     if (ensureMsgf(TLG_Data_Enemy_Current, TEXT("Skip Location_Enter or can be crit error")) != true)
         return;

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Dialogue::Init(ATLG_HUD *tlg_hud, ATLG_Player_State *tlg_player_state)
{
	TLG_HUD = tlg_hud;
    TLG_Player_State = tlg_player_state;
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Dialogue::Dialogue_Start(const FName &row_id)
{
    static const FString context(TEXT("Dialogue Context") );

    if (DT_Dialogue_Current != 0)
    {
        if (FDialogue_Node *dialogue_node_next = DT_Dialogue_Current->FindRow<FDialogue_Node>(row_id, context, true) )  // Find node by row id
        {
            if (UTexture2D *texture_portrait_for_mood = TLG_Data_Enemy_Current->Get_Portrait_For_Mood(dialogue_node_next->Tag_Portrait) )
                TLG_HUD->Set_Image_Texture_Portrait(texture_portrait_for_mood);
            TLG_HUD->Dialogue_Node_Show(*dialogue_node_next);  // Send data to Dialogue UI
        }
    }
    else
        Dialogue_End();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Dialogue::Dialogue_End()
{
    TLG_HUD->Dialogue_Hide();

     On_Dialogue_Ended.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Dialogue::Handle_Player_Decision(const FPlayer_Response &player_response)
{
    TLG_Player_State->Apply_Multy_Dynamic_Change(player_response.Set_By_Caller_Magnitude);

    // 1.1. Show next dialugue if next row exists
    if (player_response.Row_ID_Next.IsNone() != true)
        Dialogue_Start(player_response.Row_ID_Next);
    else
        Dialogue_End();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Dialogue::Set_Dialogue_Current(UDataTable* data_table)
{
    DT_Dialogue_Current = data_table;
}
//------------------------------------------------------------------------------------------------------------

