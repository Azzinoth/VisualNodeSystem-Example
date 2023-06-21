#include "FEVisualNodeSystem.h"
#include "CustomNode.h"
#include "CustomNode2.h"
#include "CustomNode3.h"

void DrawNodeAreaWindow(FEVisualNodeArea* NodeArea)
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
	APPLICATION.InitWindow(WindowSize.x, WindowSize.y, "FEVisualNodeSystem example");

	FEVisualNodeArea* NodeArea = nullptr;

	NodeArea = NODE_SYSTEM.CreateNodeArea();
	// This new function does not break other projects.
	NodeArea->SetIsAreaFillingWindow(true);

	// Need to place that node in the center of the screen
	FEVisualNode* DefaultNode = new FEVisualNode();
	DefaultNode->SetName("Default node");
	DefaultNode->AddInputSocket(new FEVisualNodeSocket(DefaultNode, FE_NODE_SOCKET_FLOAT_CHANNEL_IN, "in"));
	DefaultNode->AddOutputSocket(new FEVisualNodeSocket(DefaultNode, FE_NODE_SOCKET_FLOAT_CHANNEL_OUT, "out"));
	DefaultNode->SetPosition(ImVec2(WindowSize.x / 2 - DefaultNode->GetSize().x / 2, 200));
	NodeArea->AddNode(DefaultNode);
	
	FEVisualNode* RoundNode = new FEVisualNode();
	RoundNode->SetStyle(FE_VISUAL_NODE_STYLE_CIRCLE);
	RoundNode->SetName("Round node");
	RoundNode->AddInputSocket(new FEVisualNodeSocket(RoundNode, FE_NODE_SOCKET_FLOAT_CHANNEL_IN, "in"));
	RoundNode->AddOutputSocket(new FEVisualNodeSocket(RoundNode, FE_NODE_SOCKET_FLOAT_CHANNEL_OUT, "out"));
	RoundNode->SetPosition(ImVec2(WindowSize.x / 2 - RoundNode->GetSize().x / 2, 350));
	NodeArea->AddNode(RoundNode);

	// Custom node
	CustomNode* CustomNodeExample = new CustomNode();
	CustomNodeExample->SetPosition(ImVec2(WindowSize.x / 2 - CustomNodeExample->GetSize().x / 2, 490));
	NodeArea->AddNode(CustomNodeExample);
	
	// Some simple rules on sockets
	CustomNode2* CustomNode2Example = new CustomNode2();
	CustomNode2Example->SetPosition(ImVec2(30.0f, 40.0f));
	NodeArea->AddNode(CustomNode2Example);

	CustomNode3* CustomNode3Example = new CustomNode3();
	CustomNode3Example->SetPosition(ImVec2(WindowSize.x / 2.0f - CustomNode3Example->GetSize().x / 2.0f, 40.0f));
	NodeArea->AddNode(CustomNode3Example);

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