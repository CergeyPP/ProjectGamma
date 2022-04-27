#pragma once
class PhysicElement
{
public:

	virtual void prepareToSimulation() = 0;
	virtual void fetchResults() = 0;
};

