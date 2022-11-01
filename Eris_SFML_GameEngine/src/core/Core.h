#pragma once

namespace EGE {

class Core {
public:		// constructors
	Core() {}
	virtual ~Core() {}
public:
	static void setDtPtr(float* dt) {
		Log::Get().assert_(__FUNCTION__, __LOG_FILENAME__, __LINE__, p_dt, "TRIED TO CHANGE DT POINTER"); 
		if (p_dt) __debugbreak();
		p_dt = dt;
	}

protected:
	inline const float& getDt() const { return *p_dt; }
	inline const float& dt() const { return *p_dt; }
private:
	static float* p_dt;

};

}
