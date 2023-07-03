#include "CustomNode4.h"

bool CustomNode4::isRegistered = []()
{
	NODE_FACTORY.RegisterNodeType("CustomNode4",
		[]() -> VisualNode* {
			return new CustomNode4();
		},

		[](const VisualNode& Node) -> VisualNode* {
			const CustomNode4& NodeToCopy = static_cast<const CustomNode4&>(Node);
			return new CustomNode4(NodeToCopy);
		}
	);

	return true;
}();

CustomNode4::CustomNode4() : VisualNode()
{
	Type = "CustomNode4";

	SetStyle(VISUAL_NODE_STYLE_DEFAULT);

	SetSize(ImVec2(370, 130));
	SetName("CustomNode4");

	TitleBackgroundColor = ImColor(128, 117, 208);
	TitleBackgroundColorHovered = ImColor(135, 145, 255);
	
	AddSocket(new NodeSocket(this, "FLOAT", "in", false));
}

CustomNode4::CustomNode4(const CustomNode4& Src) : VisualNode(Src)
{
	Data = Src.Data;

	SetStyle(VISUAL_NODE_STYLE_DEFAULT);
}

void CustomNode4::SetStyle(VISUAL_NODE_STYLE NewValue)
{
	// Do nothing. We don't want to change style
}

void CustomNode4::Draw()
{	
	VisualNode::Draw();

	ImVec2 NodePosition = ImGui::GetCursorScreenPos();
	ImVec2 NodeSize = GetSize();

	ImGui::SetCursorScreenPos(NodePosition + ImVec2(55.0f, 50.0f));
	ImGui::Text("Node demonstrate socket events");

	ImGui::SetCursorScreenPos(NodePosition + ImVec2(55.0f, 70.0f));
	std::string OutputText = "Last socket event: \n" + LastSocketEventDiscription;
	ImGui::Text(OutputText.c_str());
}

void CustomNode4::SocketEvent(NodeSocket* OwnSocket, NodeSocket* ConnectedSocket, VISUAL_NODE_SOCKET_EVENT EventType)
{
	VisualNode::SocketEvent(OwnSocket,  ConnectedSocket, EventType);

	std::string EventTypeStr = "Unknown";
	switch (EventType)
	{
		case VISUAL_NODE_SOCKET_CONNECTED:
			EventTypeStr = "Connected";
		break;

		case VISUAL_NODE_SOCKET_DISCONNECTED:
			EventTypeStr = "Disconnected";
		break;

		case VISUAL_NODE_SOCKET_DESTRUCTION:
			EventTypeStr = "Destruction";
		break;

		case VISUAL_NODE_SOCKET_UPDATE:
			EventTypeStr = "Update";
		break;
	}

	LastSocketEventDiscription = "Node ID: " + ConnectedSocket->GetParent()->GetID() + "\nEvent type: " + EventTypeStr;
}

float CustomNode4::GetData()
{
	return Data;
}

bool CustomNode4::CanConnect(NodeSocket* OwnSocket, NodeSocket* CandidateSocket, char** MsgToUser)
{
	if (!VisualNode::CanConnect(OwnSocket, CandidateSocket, nullptr))
		return false;

	return true;
}