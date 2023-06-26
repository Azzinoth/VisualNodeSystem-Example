#include "VisualNodeSystem.h"
#include "CustomNode.h"
#include "CustomNode2.h"
#include "CustomNode3.h"
#include "CustomNode4.h"

void DrawNodeAreaWindow(VisualNodeArea* NodeArea)
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	static bool ShowDemoWindow = true;

	if (ImGui::Begin("Nodes area", &ShowDemoWindow, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
	{
		NodeArea->Update();
	}
	ImGui::End();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ImVec2 WindowSize = ImVec2(1280, 720);
	APPLICATION.InitWindow(WindowSize.x, WindowSize.y, "VisualNodeSystem example");

	VisualNodeArea* NodeArea = nullptr;

	NodeArea = NODE_SYSTEM.CreateNodeArea();
	// This new function does not break other projects.
	NodeArea->SetIsAreaFillingWindow(true);

	// Need to place that node in the center of the screen
	VisualNode* DefaultNode = new VisualNode();
	DefaultNode->SetName("Default node");
	DefaultNode->AddSocket(new NodeSocket(DefaultNode, "FLOAT", "in", false));
	DefaultNode->AddSocket(new NodeSocket(DefaultNode, "FLOAT", "out", true));
	DefaultNode->SetPosition(ImVec2(WindowSize.x / 2.0f - DefaultNode->GetSize().x / 2.0f, 200.0f));
	NodeArea->AddNode(DefaultNode);
	
	VisualNode* RoundNode = new VisualNode();
	RoundNode->SetStyle(VISUAL_NODE_STYLE_CIRCLE);
	RoundNode->SetName("Round node");
	RoundNode->AddSocket(new NodeSocket(RoundNode, "FLOAT", "in", false));
	RoundNode->AddSocket(new NodeSocket(RoundNode, "FLOAT", "out", true));
	RoundNode->SetPosition(ImVec2(WindowSize.x / 2.0f - RoundNode->GetSize().x / 2.0f, 350.0f));
	NodeArea->AddNode(RoundNode);

	// Custom node
	CustomNode* CustomNodeExample = new CustomNode();
	CustomNodeExample->SetPosition(ImVec2(WindowSize.x / 2.0f - CustomNodeExample->GetSize().x / 2, 490.0f));
	NodeArea->AddNode(CustomNodeExample);
	
	// Some simple rules on sockets
	CustomNode2* CustomNode2Example = new CustomNode2();
	CustomNode2Example->SetPosition(ImVec2(30.0f, 40.0f));
	NodeArea->AddNode(CustomNode2Example);

	CustomNode3* CustomNode3Example = new CustomNode3();
	CustomNode3Example->SetPosition(ImVec2(WindowSize.x / 2.0f - CustomNode3Example->GetSize().x / 2.0f, 40.0f));
	NodeArea->AddNode(CustomNode3Example);

	// Sockets events.
	CustomNode4* CustomNode4Example = new CustomNode4();
	CustomNode4Example->SetPosition(ImVec2(850.0f, 250.0f));
	NodeArea->AddNode(CustomNode4Example);

	while (APPLICATION.IsWindowOpened())
	{
		APPLICATION.BeginFrame();

		glClearColor(0.6, 0.85, 0.917, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		DrawNodeAreaWindow(NodeArea);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save nodes to Save.nodes file"))
				{
					NodeArea->SaveToFile("Save.nodes");
				}

				DWORD dwAttrib = GetFileAttributesA("Save.nodes");
				if (!(dwAttrib != INVALID_FILE_ATTRIBUTES &&
					!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)))
					ImGui::BeginDisabled();

				if (ImGui::MenuItem("Load nodes from Save.nodes file"))
				{
					NodeArea->Clear();
					NodeArea->LoadFromFile("Save.nodes");
				}

				if (!(dwAttrib != INVALID_FILE_ATTRIBUTES &&
					!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)))
					ImGui::EndDisabled();

				if (ImGui::MenuItem("Exit"))
				{
					APPLICATION.Terminate();
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		ImGui::PopStyleVar();

		APPLICATION.EndFrame();
	}
	
	return 0;
}