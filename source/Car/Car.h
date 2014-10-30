class Car
{

	struct CarMetrics
	{
		float currentDirection;
		float distanceMoved; 

	};
	
	public:
		Car();

		CarMetrics* getCurrentLocation();
		void onActivateOilSlick();
		void onActivateRedShell();
		void onActivateBananaPeel();
		void onActivateMushroom();
		
	private:
		Void* readFromCompass();
		Void* readCurrentLinearMovement();

};



