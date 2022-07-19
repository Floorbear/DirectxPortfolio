#pragma once
#include "DNFLevel.h"

class SeriaRoom : public DNFLevel
{
public:
	SeriaRoom();
	~SeriaRoom();

	SeriaRoom(const SeriaRoom& _Other) = delete;
	SeriaRoom(const SeriaRoom&& _Other) noexcept = delete;
	SeriaRoom& operator=(const SeriaRoom& _Ohter) = delete;
	SeriaRoom& operator=(const SeriaRoom&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	int Value_;
};

