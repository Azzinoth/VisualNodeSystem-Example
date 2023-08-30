#include "VisualNodeSystem.h"
using namespace VisNodeSys;

#include "CustomNode.h"
#include "CustomNode2.h"
#include "CustomNode3.h"
#include "CustomNode4.h"
#include "CustomNodeStyleDemonstration.h"

// ********** SETING UP WINODW AND IMGUI ********** //

#include "imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#define GLEW_STATIC
#include "GL/glew.h"
#include "GL/wglew.h"

#include <GLFW/glfw3.h>
#include <GL/GL.h>

GLFWwindow* Window;
void InitWindow(const int Width, const int Height, std::string WindowTitle)
{
	glfwInit();

	Window = glfwCreateWindow(Width, Height, WindowTitle.c_str(), nullptr, nullptr);
	if (!Window)
		glfwTerminate();

	glfwMakeContextCurrent(Window);
	glewInit();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(Window, true);
	ImGui_ImplOpenGL3_Init("#version 410");
}

void BeginFrame()
{
	ImGui::GetIO().DeltaTime = 1.0f / 60.0f;
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void EndFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(Window);
	glfwPollEvents();
}

// ********** SETING UP WINODW AND IMGUI END ********** //

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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ImVec2 WindowSize = ImVec2(1280, 720);
	InitWindow(static_cast<int>(WindowSize.x), static_cast<int>(WindowSize.y), "VisualNodeSystem example");

	NODE_SYSTEM.Initialize();

	NodeArea* NodeArea = nullptr;
	NodeArea = NODE_SYSTEM.CreateNodeArea();
	NodeArea->SetIsFillingWindow(true);

	// Need to place that node in the center of the screen
	Node* DefaultNode = new Node();
	DefaultNode->SetName("Default node");
	DefaultNode->AddSocket(new NodeSocket(DefaultNode, "EXEC", "in", false));
	DefaultNode->AddSocket(new NodeSocket(DefaultNode, "EXEC", "out", true));
	DefaultNode->SetPosition(ImVec2(WindowSize.x / 2.0f - DefaultNode->GetSize().x / 2.0f, 250.0f));
	NodeArea->AddNode(DefaultNode);
	
	Node* RoundNode = new Node();
	RoundNode->SetStyle(CIRCLE);
	RoundNode->SetName("Round node");
	RoundNode->AddSocket(new NodeSocket(RoundNode, "EXEC", "in", false));
	RoundNode->AddSocket(new NodeSocket(RoundNode, "EXEC", "out", true));
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
	RerouteDemostrationNode->AddSocket(new NodeSocket(RerouteDemostrationNode, "EXEC", "out", true));
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
	RerouteDemostrationNodeEnd->AddSocket(new NodeSocket(RerouteDemostrationNodeEnd, "EXEC", "in", false));
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

	while (!glfwWindowShouldClose(Window))
	{
		BeginFrame();

		glClearColor(0.6f, 0.85f, 0.917f, 1.0f);
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
					glfwSetWindowShouldClose(Window, true);
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		ImGui::PopStyleVar();

		EndFrame();
	}
	
	return 0;
}