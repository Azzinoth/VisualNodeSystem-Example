#include "SubSystems/FEBasicApplication/FEBasicApplication.h"
using namespace FocalEngine;

#include "VisualNodeSystem.h"
using namespace VisNodeSys;

#include "CustomNode.h"
#include "CustomNode2.h"
#include "CustomNode3.h"
#include "CustomNode4.h"
#include "CustomNodeStyleDemonstration.h"

#include <filesystem>

void DrawNodeAreaWindow(NodeArea* NodeArea)
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

void DrawMainMenuBar(NodeArea* NodeArea)
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save nodes to Save.nodes file"))
			{
				NodeArea->SaveToFile("Save.nodes");
			}

			std::error_code ErrorCode;
			const bool bSaveFileExists = std::filesystem::is_regular_file("Save.nodes", ErrorCode);
			if (!bSaveFileExists)
				ImGui::BeginDisabled();

			if (ImGui::MenuItem("Load nodes from Save.nodes file"))
			{
				NodeArea->Clear();
				NodeArea->LoadFromFile("Save.nodes");
			}

			if (!bSaveFileExists)
				ImGui::EndDisabled();

			// A browser tab can not be closed by the application.
#if !FE_PLATFORM(EMSCRIPTEN)
			if (ImGui::MenuItem("Exit"))
			{
				APPLICATION.Close();
			}
#endif

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	ImGui::PopStyleVar();
}

#if FE_PLATFORM(WINDOWS)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char** argv)
#endif
{
	ImVec2 WindowSize = ImVec2(1280, 720);
	FEWindow* MainWindow = APPLICATION.AddWindow(static_cast<int>(WindowSize.x), static_cast<int>(WindowSize.y), "VisualNodeSystem example");
	MainWindow->SetClearColor(0.6f, 0.85f, 0.917f, 1.0f);

	NODE_SYSTEM.Initialize();

	NodeArea* NodeArea = nullptr;
	NodeArea = NODE_SYSTEM.CreateNodeArea();
	NodeArea->SetIsFillingWindow(true);

	// Need to place that node in the center of the screen
	Node* DefaultNode = new Node();
	DefaultNode->SetName("Default node");
	DefaultNode->AddSocket(new NodeSocket(DefaultNode, "EXEC", "in", NodeSocket::SocketFlow::Input));
	DefaultNode->AddSocket(new NodeSocket(DefaultNode, "EXEC", "out", NodeSocket::SocketFlow::Output));
	DefaultNode->SetPosition(ImVec2(WindowSize.x / 2.0f - DefaultNode->GetSize().x / 2.0f, 250.0f));
	NodeArea->AddNode(DefaultNode);

	Node* RoundNode = new Node();
	RoundNode->SetStyle(CIRCLE);
	RoundNode->SetName("Round node");
	RoundNode->AddSocket(new NodeSocket(RoundNode, "EXEC", "in", NodeSocket::SocketFlow::Input));
	RoundNode->AddSocket(new NodeSocket(RoundNode, "EXEC", "out", NodeSocket::SocketFlow::Output));
	RoundNode->SetPosition(ImVec2(WindowSize.x / 2.0f - RoundNode->GetSize().x / 2.0f, 400.0f));
	NodeArea->AddNode(RoundNode);

	// Custom node
	CustomNode* CustomNodeExample = new CustomNode();
	CustomNodeExample->SetPosition(ImVec2(WindowSize.x / 2.0f - CustomNodeExample->GetSize().x / 2, 540.0f));
	NodeArea->AddNode(CustomNodeExample);

	// Some simple rules on sockets
	CustomNode2* CustomNode2Example = new CustomNode2();
	CustomNode2Example->SetPosition(ImVec2(10.0f, 40.0f));
	CustomNode2Example->SetSize(CustomNode2Example->GetSize() + ImVec2(20.0f, 0.0f));
	NodeArea->AddNode(CustomNode2Example);

	CustomNode3* CustomNode3Example = new CustomNode3();
	CustomNode3Example->SetPosition(ImVec2(WindowSize.x / 2.0f - CustomNode3Example->GetSize().x / 2.0f, 40.0f));
	CustomNode3Example->SetSize(CustomNode3Example->GetSize() + ImVec2(80.0f, 0.0f));
	NodeArea->AddNode(CustomNode3Example);

	// Sockets events.
	CustomNode4* CustomNode4Example = new CustomNode4();
	CustomNode4Example->SetPosition(ImVec2(850.0f, 360.0f));
	NodeArea->AddNode(CustomNode4Example);

	// Socket style.
	CustomNodeStyleDemonstration* CustomNode5Example = new CustomNodeStyleDemonstration();
	CustomNode5Example->SetPosition(ImVec2(10.0f, 250.0f));
	CustomNode5Example->SetSize(CustomNode5Example->GetSize() + ImVec2(80.0f, 10.0f));
	NodeArea->AddNode(CustomNode5Example);

	CustomNodeStyleDemonstration* CustomNode6Example = new CustomNodeStyleDemonstration();
	CustomNode6Example->SetPosition(ImVec2(300.0f, 250.0f));
	NodeArea->AddNode(CustomNode6Example);

	NodeArea->TryToConnect(CustomNode5Example, 0, CustomNode6Example, 0);
	NodeArea->TryToConnect(CustomNode5Example, 1, CustomNode6Example, 1);
	NodeArea->TryToConnect(CustomNode5Example, 2, CustomNode6Example, 2);
	NodeArea->TryToConnect(CustomNode5Example, 3, CustomNode6Example, 3);

	// Demonstration of reroute nodes.
	Node* RerouteDemostrationNode = new Node();
	RerouteDemostrationNode->SetName("Some node");
	RerouteDemostrationNode->AddSocket(new NodeSocket(RerouteDemostrationNode, "EXEC", "out", NodeSocket::SocketFlow::Output));
	RerouteDemostrationNode->SetSize(RerouteDemostrationNode->GetSize() - ImVec2(80.0f, 0.0f));
	RerouteDemostrationNode->SetPosition(ImVec2(10.0f, 490.0f));
	NodeArea->AddNode(RerouteDemostrationNode);

	Node* RerouteDemostrationNodeMiddle = new Node();
	RerouteDemostrationNodeMiddle->SetName("Node in between");
	RerouteDemostrationNodeMiddle->SetSize(RerouteDemostrationNodeMiddle->GetSize() - ImVec2(70.0f, 0.0f));
	RerouteDemostrationNodeMiddle->SetPosition(ImVec2(180.0f, 490.0f));
	NodeArea->AddNode(RerouteDemostrationNodeMiddle);

	Node* RerouteDemostrationNodeEnd = new Node();
	RerouteDemostrationNodeEnd->SetName("Some node");
	RerouteDemostrationNodeEnd->AddSocket(new NodeSocket(RerouteDemostrationNodeEnd, "EXEC", "in", NodeSocket::SocketFlow::Input));
	RerouteDemostrationNodeEnd->SetSize(RerouteDemostrationNodeEnd->GetSize() - ImVec2(80.0f, 0.0f));
	RerouteDemostrationNodeEnd->SetPosition(ImVec2(350.0f, 490.0f));
	NodeArea->AddNode(RerouteDemostrationNodeEnd);

	NodeArea->TryToConnect(RerouteDemostrationNode, 0, RerouteDemostrationNodeEnd, 0);
	int SegmentIndex = 0;
	NodeArea->AddRerouteNodeToConnection(RerouteDemostrationNode, 0, RerouteDemostrationNodeEnd, 0, SegmentIndex, ImVec2(190.0f, 470.0f));
	NodeArea->AddRerouteNodeToConnection(RerouteDemostrationNode, 0, RerouteDemostrationNodeEnd, 0, SegmentIndex + 1, ImVec2(312.0f, 470.0f));

	// In previous example SegmentIndex would be 0 and 1.
	// But in real project you would need to know already existing reroute nodes(segments).
	// GetConnectionSegments function will give you vector of pair(begin and end coordinates) for each segment.
	std::vector<std::pair<ImVec2, ImVec2>> Segments = NodeArea->GetConnectionSegments(RerouteDemostrationNode, 0, RerouteDemostrationNodeEnd, 0);

	// Add group comment to demonstrate how user can highlight node collections, signifying their combined functionality.
	GroupComment* GroupCommentExample = new GroupComment();
	GroupCommentExample->SetPosition(ImVec2(520.0f, 180.0f));
	GroupCommentExample->SetSize(ImVec2(710.0f, 500.0f));
	GroupCommentExample->SetCaption("Group of some nodes");
	NodeArea->AddGroupComment(GroupCommentExample);

	// NodeArea is captured by value, because on the web APPLICATION.Run never returns to main.
	MainWindow->SetRenderFunction([NodeArea]() {
		DrawNodeAreaWindow(NodeArea);
		DrawMainMenuBar(NodeArea);
	});

	APPLICATION.Run([]() {
		APPLICATION.BeginFrame();
		APPLICATION.RenderWindows();
		APPLICATION.EndFrame();
	});

	return 0;
}
