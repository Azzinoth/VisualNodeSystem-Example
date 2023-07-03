#include "CustomNode.h"

bool CustomNode::isRegistered = []()
{
	NODE_FACTORY.RegisterNodeType("CustomNode",
		[]() -> VisualNode* {
			return new CustomNode();
		},

		[](const VisualNode& Node) -> VisualNode* {
			const CustomNode& NodeToCopy = static_cast<const CustomNode&>(Node);
			return new CustomNode(NodeToCopy);
		}
	);

	return true;
}();

CustomNode::CustomNode() : VisualNode()
{
	Type = "CustomNode";
	bCouldBeDestroyed = false;

	SetStyle(VISUAL_NODE_STYLE_DEFAULT);

	SetSize(ImVec2(220, 78));
	SetName("CustomNode");

	TitleBackgroundColor = ImColor(31, 117, 208);
	TitleBackgroundColorHovered = ImColor(35, 145, 255);
	
	AddSocket(new NodeSocket(this, "FLOAT", "out", true));
}

CustomNode::CustomNode(const CustomNode& Src) : VisualNode(Src)
{
	Data = Src.Data;
	bCouldBeDestroyed = false;

	SetStyle(VISUAL_NODE_STYLE_DEFAULT);
}

void CustomNode::SetStyle(VISUAL_NODE_STYLE NewValue)
{
	// Do nothing. We don't want to change style
}

void CustomNode::Draw()
{	
	VisualNode::Draw();

	ImVec2 NodePosition = ImGui::GetCursorScreenPos();
	ImVec2 NodeSize = GetSize();

	ImGui::SetCursorScreenPos(NodePosition + ImVec2(5.0f, 34.0f));
	ImGui::Text("This is custom node");

	ImGui::SetCursorScreenPos(NodePosition + ImVec2(5.0f, 55.0f));
	ImGui::Text("User non-deletable node.");
}

void CustomNode::SocketEvent(NodeSocket* OwnSocket, NodeSocket* ConnectedSocket, VISUAL_NODE_SOCKET_EVENT EventType)
{
	VisualNode::SocketEvent(OwnSocket,  ConnectedSocket, EventType);
}

float CustomNode::GetData()
{
	return Data;
}

bool CustomNode::CanConnect(NodeSocket* OwnSocket, NodeSocket* CandidateSocket, char** MsgToUser)
{
	if (!VisualNode::CanConnect(OwnSocket, CandidateSocket, nullptr))
		return false;

	return false;
}