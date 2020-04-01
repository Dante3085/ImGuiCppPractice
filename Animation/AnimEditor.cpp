#include "AnimEditor.h"

#include <iostream>
#include <algorithm>

#include "imgui.h"
#include "imgui-SFML.h"

AnimEditor::AnimEditor()
	:
	indexCurrentAnim { 0 },
	animNameBuffer { "" },
	spritesheets { Spritesheets::getInstance() },
	animSprite { sf::Vector2f { 0, 0 }}
{

}

//void AnimEditor::update()
//{
//	// Begin Window
//	ImGui::Begin("AnimEditor");
//
//	if (ImGui::Button("Add Animation"))
//	{
//		// Create new Animtion object
//		Animation newAnim;
//
//		// Put given Animation name from InputText Widget into Animation object
//		newAnim.name = newAnimNameBuff.data();
//
//		// Put new Animation into List of Animations
//		animations.push_back(newAnim);
//
//		// Create new Buffer for InputText to manipulate name of new Animation.
//		// Each Animation has a Input Text 
//		changeAnimNameBuffs.push_back(newAnimNameBuff);
//	}
//	ImGui::InputText("AnimName", newAnimNameBuff.data(), 256);
//
//	updateAnimTree();
//
//	ImGui::End();
//}
//
//void AnimEditor::updateAnimTree()
//{
//	std::string headerName = "Animations(" + std::to_string(animations.size()) + ")";
//	if (!ImGui::CollapsingHeader(headerName.c_str()))
//		return;
//
//	for (int i = 0; i < animations.size(); ++i)
//	{
//		Animation& anim = animations[i];
//
//		if (ImGui::TreeNode(anim.name.c_str()))
//		{
//			if (ImGui::InputText("AnimName", changeAnimNameBuffs[i].data(), 256, 
//				ImGuiInputTextFlags_EnterReturnsTrue))
//			{
//				anim.name = changeAnimNameBuffs[i].data();
//			}
//			ImGui::Checkbox("IsLooped", &anim.isLooped);
//			ImGui::Checkbox("IsMirrored", &anim.isMirrored);
//			ImGui::SliderInt("FrameDelayMillis", &anim.frameDelayMillis, 0, 1000);
//
//			ImGui::TreePop();
//		}
//	}
//}

void AnimEditor::update(sf::Time const& deltaTime)
{
	ImGui::Begin("Animation Editor");

	animSprite.update(deltaTime);

	updateSpritesheetSubWindow();
	ImGui::SameLine();
	updateAnimationSubWindow();
	ImGui::SameLine();
	updateAnimPropsSubWindow();

	ImGui::End();
}

void AnimEditor::updateAnimPropsSubWindow()
{
	ImGui::BeginChild("Animation Properties Window", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.33f, 0), false/*, window_flags*/);

	// Add new Animation
	if (ImGui::Button("Add Animation"))
	{
		int numAnimsWithDefaultName = 0;
		for (int i = 0; i < animations.size(); ++i)
		{
			if (animations[i].name.find("NO_NAME") != std::string::npos)
				++numAnimsWithDefaultName;
		}

		Animation newAnim;
		newAnim.name = "NO_NAME_" + std::to_string(numAnimsWithDefaultName);
		animations.push_back(newAnim);

		indexCurrentAnim = animations.size() - 1;
	}

	if (animations.size() > 0)
	{
		// Search through Animations in ComboBox
		std::string comboBoxAnimsPreviewValue = animations.size() == 0 ? "NO ANIMATIONS" : animations[indexCurrentAnim].name;
		if (ImGui::BeginCombo("Animations", comboBoxAnimsPreviewValue.data()))
		{
			for (int i = 0; i < animations.size(); ++i)
			{
				bool is_selected = (indexCurrentAnim == i);
				if (ImGui::Selectable(animations[i].name.data(), is_selected))
				{
					indexCurrentAnim = i;
				}
				if (is_selected)
					ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
			}
			ImGui::EndCombo();
		}
		// Change name of current Animation
		if (ImGui::InputText("Name", animNameBuffer.data(), 256, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			animations[indexCurrentAnim].name = animNameBuffer.data();
		}

		ImGui::Checkbox("IsLooped", &animations[indexCurrentAnim].isLooped);
		ImGui::Checkbox("IsMirrored", &animations[indexCurrentAnim].isMirrored);
		ImGui::SliderInt("FrameDelayMillis", &animations[indexCurrentAnim].frameDelayMillis, 0, 1000);

		std::string comboBoxSpritesheetsPreviewValue;
		if (spritesheets.getNumSpritesheets() == 0)
		{
			comboBoxSpritesheetsPreviewValue = "No Spritesheets(0)";
		}
		else if (animations[indexCurrentAnim].spritesheet == nullptr)
		{
			comboBoxSpritesheetsPreviewValue = "Choose Spritesheet(" + std::to_string(spritesheets.getNumSpritesheets()) + ")";
		}
		else
		{
			comboBoxSpritesheetsPreviewValue = animations[indexCurrentAnim].spritesheet->name;
		}

		if (ImGui::BeginCombo("Spritesheets", comboBoxSpritesheetsPreviewValue.data()))
		{
			Animation& currentAnim = animations[indexCurrentAnim];

			std::vector<std::string> sheetNames = spritesheets.getSheetNames();
			for (int i = 0; i < sheetNames.size(); ++i)
			{
				bool is_selected = currentAnim.spritesheet != nullptr ? currentAnim.spritesheet->name == sheetNames[i] : false ? true : false;
				if (ImGui::Selectable(sheetNames[i].data(), is_selected))
				{
					currentAnim.spritesheet = &spritesheets.getSpritesheet(sheetNames[i]);
				}
			}

			ImGui::EndCombo();
		}

		if (ImGui::Button("Add Frame"))
		{
			animations[indexCurrentAnim].frames.push_back(sf::IntRect(0, 0, 0, 0));
			animations[indexCurrentAnim].frameOffsets.push_back(sf::Vector2i(0, 0));
		}

		ImGui::SameLine();

		static int indexFrameToRemove = 0;

		if (ImGui::Button("Remove Frame"))
		{
			Animation& currentAnim = animations[indexCurrentAnim];

			// Only try to remove when there is something to remove.
			if (currentAnim.frames.size() != 0)
			{
				currentAnim.frames.erase(currentAnim.frames.begin() + indexFrameToRemove);
				currentAnim.frameOffsets.erase(currentAnim.frameOffsets.begin() + indexFrameToRemove);

				// In case we just removed the previously last frame,
				// we need to correct the index since it would be invalid.
				if (indexFrameToRemove == currentAnim.frames.size() &&
					currentAnim.frames.size() != 0)
					--indexFrameToRemove;

			}
		}

		ImGui::SameLine();

		ImGui::PushItemWidth(100);
		if (ImGui::SliderInt("FrameToRemove", &indexFrameToRemove, 0, animations[indexCurrentAnim].frames.size() - 1))
		{
			std::cout << indexFrameToRemove << std::endl;
		}
		ImGui::PopItemWidth();


		// TODO: Frames ComboBox
		std::string comboBoxFramesPreviewValue = "Frames(" + std::to_string(animations[indexCurrentAnim].frames.size()) + ")";
		if (ImGui::BeginCombo("Frames", comboBoxFramesPreviewValue.data()))
		{
			// TODO: Why do all Widgets react when only one is actually interacted with ?
			// This is an ID problem. Interactable Widgets create their unique id s by creating
			// a hash with the Window name, their name and maybe the name of the tree they are in.
			// See FAQ: https://github.com/ocornut/imgui/blob/master/docs/FAQ.md#q-why-are-multiple-widgets-reacting-when-i-interact-with-a-single-one-q-how-can-i-have-multiple-widgets-with-the-same-label-or-with-an-empty-label

			// 99.740 Hyuks

			Animation& currentAnim = animations[indexCurrentAnim];
			for (int i = 0; i < animations[indexCurrentAnim].frames.size(); ++i)
			{
				std::string iStr = std::to_string(i);
				std::string x = "x##Frame" + iStr;
				std::string y = "y##Frame" + iStr;
				std::string width = "width##Frame" + iStr;
				std::string height = "height##Frame" + iStr;
				std::string frame = "Frame " + iStr;

				ImGui::Text(frame.data());
				ImGui::SameLine();

				ImGui::InputInt(x.data(), &currentAnim.frames[i].left);
				ImGui::SameLine();
				ImGui::InputInt(y.data(), &currentAnim.frames[i].top);
				ImGui::SameLine();
				ImGui::InputInt(width.data(), &currentAnim.frames[i].width);
				ImGui::SameLine();
				ImGui::InputInt(height.data(), &currentAnim.frames[i].height);
			}

			ImGui::EndCombo();
		}

		std::string comboBoxFrameOffsetsPreviewValue = "FrameOffsets(" + std::to_string(animations[indexCurrentAnim].frameOffsets.size()) + ")";
		if (ImGui::BeginCombo("FrameOffsets", comboBoxFrameOffsetsPreviewValue.data()))
		{
			Animation& currentAnim = animations[indexCurrentAnim];
			for (int i = 0; i < animations[indexCurrentAnim].frames.size(); ++i)
			{
				std::string iStr = std::to_string(i);
				std::string x = "x##Frame" + iStr;
				std::string y = "y##Frame" + iStr;
				std::string frameOffset = "FrameOffset " + iStr;

				ImGui::Text(frameOffset.data());
				ImGui::SameLine();

				ImGui::InputInt(x.data(), &currentAnim.frameOffsets[i].x);
				ImGui::SameLine();
				ImGui::InputInt(y.data(), &currentAnim.frameOffsets[i].y);
			}

			ImGui::EndCombo();
		}

		if (ImGui::Button("Print Anim"))
		{
			std::cout << animations[indexCurrentAnim].toString() << std::endl;
		}

		if (ImGui::Button("Remove Animation"))
		{
			animations.erase(animations.begin() + indexCurrentAnim);
			indexCurrentAnim = 0;
		}
	}

	ImGui::EndChild();
}

void AnimEditor::updateSpritesheetSubWindow()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
	ImGui::BeginChild("Spritesheet Window", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.33f, 0), true/*, window_flags*/);

	ImGui::Text("Test Spritesheet Window");

	ImGui::EndChild();
}

void AnimEditor::updateAnimationSubWindow()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
	ImGui::BeginChild("Animation Window", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.33f, 0), true, window_flags);

	if (animations.size() != 0 && animations[indexCurrentAnim].spritesheet != nullptr)
	{
		animSprite.setAnimation(&animations[indexCurrentAnim]);
		ImGui::Image(animSprite.getSprite());
	}

	ImGui::EndChild();
}