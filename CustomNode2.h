#pragma once

#include "SubSystems/VisualNodeSystem/VisualNodeSystem.h"

class CustomNode2 : public VisualNode
{
	friend class NodeFactory;
	static bool isRegistered;

	float Data = 0.0f;

	bool CanConnect(NodeSocket* OwnSocket, NodeSocket* CandidateSocket, char** MsgToUser);
	void SocketEvent(NodeSocket* OwnSocket, NodeSocket* ConnectedSocket, VISUAL_NODE_SOCKET_EVENT EventType);

	// Make it private
	void SetStyle(VISUAL_NODE_STYLE NewValue);
public:
	CustomNode2();
	CustomNode2(const CustomNode2& Src);

	void Draw();
	float GetData();
};