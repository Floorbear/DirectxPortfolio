#include "PreCompile.h"
#include "DNFAvatarGUI.h"

#include "DNFGlobalValue.h"
#include "Player_Main.h"

DNFAvatarGUI::DNFAvatarGUI()
{
}

DNFAvatarGUI::~DNFAvatarGUI()
{
}

void DNFAvatarGUI::Initialize(GameEngineLevel* _Level)
{
}

void DNFAvatarGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
    if(DNFGlobalValue::CurrentLevel != nullptr)
    {
        Player_Main* Player = DNFGlobalValue::CurrentLevel->GetPlayer();
        //무기
        {
            ImGui::Text("Weapon");
            GameEngineFolderTexture* DefaultWeapon = GameEngineFolderTexture::Find("club0000c");
            GameEngineFolderTexture* JobWeapon = GameEngineFolderTexture::Find("lswd3400c");
            ImGui::BeginChildFrame((ImGuiID)"WeaponSelect", { 115 * 2 , 115 * 1 });

            GameEngineTexture* Image = DefaultWeapon->GetTexture(242);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Weapon);
            }
            ImGui::SameLine();

            Image = JobWeapon->GetTexture(242);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Job, AvatarParts::Weapon);
            }

            ImGui::EndChildFrame();
        }
        //헤어
        {
            ImGui::Text("Hair");
            //일반 헤어
            GameEngineFolderTexture* DefaultHair = GameEngineFolderTexture::Find("sm_hair0000a");
            //전직압 헤어""
            GameEngineFolderTexture* JobHair = GameEngineFolderTexture::Find("A_sm_hair13000");

            ImGui::BeginChildFrame((ImGuiID)"HairSelect", { 115 * 2 , 115 * 1 });
            //일반 헤어
            GameEngineTexture* Image = DefaultHair->GetTexture(242);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Hair);
            }
            ImGui::SameLine();
            //전직 헤어
            Image = JobHair->GetTexture(242);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Job, AvatarParts::Hair);
            }
            ImGui::EndChildFrame();
        }
        //모자
        {
            ImGui::Text("Cap");
            GameEngineFolderTexture* DefaultCap = GameEngineFolderTexture::Find("None");
            GameEngineFolderTexture* DanjinCap = GameEngineFolderTexture::Find("sm_cap1500a");
            GameEngineFolderTexture* DogCap = GameEngineFolderTexture::Find("sm_cap15100c");
            ImGui::BeginChildFrame((ImGuiID)"CapSelect", { 115 * 3 , 115 * 1 });

            GameEngineTexture* Image = DefaultCap->GetTexture(0);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Cap);
            }
            ImGui::SameLine();

            Image = DanjinCap->GetTexture(242);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Danjin, AvatarParts::Cap);
            }
            ImGui::SameLine();

            Image = DogCap->GetTexture(242);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Dog, AvatarParts::Cap);
            }
            ImGui::EndChildFrame();
        }
        //상의
        {
            ImGui::Text("Coat");
            GameEngineFolderTexture* DefaultCoat = GameEngineFolderTexture::Find("sm_coat0000a");
            GameEngineFolderTexture* JobCoat = GameEngineFolderTexture::Find("sm_coat14500b");
            GameEngineFolderTexture* DogCoat = GameEngineFolderTexture::Find("sm_coat16300a");
            ImGui::BeginChildFrame((ImGuiID)"CoatSelect", { 115 * 3 , 115 * 1 });

            GameEngineTexture* Image = DefaultCoat->GetTexture(242);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Coat);
            }
            ImGui::SameLine();

            Image = JobCoat->GetTexture(242);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Job, AvatarParts::Coat);
            }
            ImGui::SameLine();

            Image = DogCoat->GetTexture(242);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Dog, AvatarParts::Coat);
            }
            ImGui::EndChildFrame();
        }
        //하의
        {
            ImGui::Text("Pants");
            GameEngineFolderTexture* DefaultPants = GameEngineFolderTexture::Find("A_sm_pants0000");
            GameEngineFolderTexture* JobPants= GameEngineFolderTexture::Find("sm_pants13600a");
            ImGui::BeginChildFrame((ImGuiID)"PantsSelect", { 115 * 2 , 115 * 1 });

            GameEngineTexture* Image = DefaultPants->GetTexture(242);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Pants);
            }
            ImGui::SameLine();

            Image = JobPants->GetTexture(242);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Job, AvatarParts::Pants);
            }

            ImGui::EndChildFrame();
        }
        //벨트
        {
            ImGui::Text("Belt");
            GameEngineFolderTexture* DefaultBelt = GameEngineFolderTexture::Find("None");
            GameEngineFolderTexture* JobBelt = GameEngineFolderTexture::Find("sm_belt10700c");
            GameEngineFolderTexture* DogBelt = GameEngineFolderTexture::Find("sm_belt12100d");
            ImGui::BeginChildFrame((ImGuiID)"BeltSelect", { 115 * 3 , 115 * 1 });

            GameEngineTexture* Image = DefaultBelt->GetTexture(0);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Belt);
            }
            ImGui::SameLine();

            Image = JobBelt->GetTexture(242);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Job, AvatarParts::Belt);
            }
            ImGui::SameLine();

            Image = DogBelt->GetTexture(242);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Dog, AvatarParts::Belt);
            }
            ImGui::EndChildFrame();
        }
        //신발
        {
            ImGui::Text("Shoes");
            GameEngineFolderTexture* DefaultShoes = GameEngineFolderTexture::Find("sm_shoes0000a");
            GameEngineFolderTexture* JobShoes = GameEngineFolderTexture::Find("sm_shoes12800a");
            GameEngineFolderTexture* DogShoes = GameEngineFolderTexture::Find("sm_shoes14500a");
            ImGui::BeginChildFrame((ImGuiID)"ShoesSelect", { 115 * 3 , 115 * 1 });

            GameEngineTexture* Image = DefaultShoes->GetTexture(242);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Shoes);
            }
            ImGui::SameLine();

            Image = JobShoes->GetTexture(242);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Job, AvatarParts::Shoes);
            }
            ImGui::SameLine();

            Image = DogShoes->GetTexture(242);
            if (ImGui::ImageButton(static_cast<ImTextureID>(Image->CreateShaderResourceView()), { 100, 100 }))
            {
                Player->AvatarManager_.ChangeAvatar(AvatarType::Dog, AvatarParts::Shoes);
            }
            ImGui::EndChildFrame();
        }



        //for (size_t i = 0; i < Texture->GetTextureCount(); i++)
        //{
        //    GameEngineTexture* TileImage = Texture->GetTexture(i);
        //    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(TileImage->CreateShaderResourceView()), { 64, 32 }))
        //    {
        //        
        //    }

        //    if (0 != (i + 1) % 5)
        //    {
        //        
        //    }
        //}

    }


}
