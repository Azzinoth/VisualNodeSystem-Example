#pragma once

#include "SubSystems/VisualNodeSystem/VisualNodeSystem.h"

VISUAL_NODE_CHILD_PRIVATE_PART(CustomNode4)
	float Data = 0.0f;

	bool CanConnect(NodeSocket* OwnSocket, NodeSocket* CandidateSocket, char** MsgToUser);
	void SocketEvent(NodeSocket* OwnSocket, NodeSocket* ConnectedSocket, VISUAL_NODE_SOCKET_EVENT EventType);

	// Make it private
	void SetStyle(VISUAL_NODE_STYLE NewValue);

	std::string LastSocketEventDiscription = "None";
public:
	CustomNode4();
	CustomNode4(const CustomNode4& Src);

	void Draw();
	float GetData();

	VisualNode* GetNextNode();
};

VISUAL_NODE_CHILD_AFTER_CLASS(CustomNode4)