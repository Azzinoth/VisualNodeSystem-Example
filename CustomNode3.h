#pragma once

#include "SubSystems/VisualNodeSystem/VisualNodeSystem.h"

class CustomNode3 : public VisualNode
{
	friend class NodeFactory;
	static bool isRegistered;

	float Data = 0.0f;

	bool CanConnect(NodeSocket* OwnSocket, NodeSocket* CandidateSocket, char** MsgToUser);
	void SocketEvent(NodeSocket* OwnSocket, NodeSocket* ConnectedSocket, VISUAL_NODE_SOCKET_EVENT EventType);

	// Make it private
	void SetStyle(VISUAL_NODE_STYLE NewValue);
public:
	CustomNode3();
	CustomNode3(const CustomNode3& Src);

	void Draw();
	float GetData();
};