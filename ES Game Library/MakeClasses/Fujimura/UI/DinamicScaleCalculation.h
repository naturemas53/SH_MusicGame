#pragma once
#include "../../../ESGLib.h"

class DinamicScaleCalculation{

public:
	DinamicScaleCalculation();
	~DinamicScaleCalculation();

	void Initialize();
	void Replay(){ this->Initialize(); }

	Vector3 UpdateScale(int elapsedMilliSecond);

	void AddScalePoint(int milliSecond, Vector3 scale);
	bool HasAddScalePoint(int milliSecond, Vector3 scale);
	void RemoveScalePoint(int milliSecond, Vector3 scale);

private:

	int totalElapsedMilliSecond_;

	struct ScalePoint{

		int milliSecond;
		Vector3 scale;

		ScalePoint(){

			this->milliSecond = 0;
			this->scale = Vector3_Zero;

		}

		ScalePoint(int delayMilliSecond,Vector3 scale){

			this->milliSecond = delayMilliSecond;
			this->scale = scale;

		}

		ScalePoint& operator=(const ScalePoint& scalePoint){

			this->milliSecond = scalePoint.milliSecond;
			this->scale = scalePoint.scale;
			return *this;

		}

		bool operator==(const ScalePoint& scalePoint){

			bool isSame = true;

			if (this->milliSecond != scalePoint.milliSecond){

				isSame = false;

			}
			if (this->scale != scalePoint.scale){

				isSame = false;

			}

			return isSame;

		}

	};

	std::vector<ScalePoint>			  scalePoints_;
	std::vector<ScalePoint>::iterator nowPoint_;

};