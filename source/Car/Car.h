struct CarMetrics
{
	float currentDirection;
	float distanceMoved;

};

class Car
{
	public:
		Car();

		CarMetrics* getCurrentLocation();
		void onActivateOilSlick();
		void onActivateRedShell();
		void onActivateBananaPeel();
		void onActivateMushroom();
		
	private:
		void* readFromCompass();
		void* readCurrentLinearMovement();

};



