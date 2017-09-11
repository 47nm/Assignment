#ifndef SubjectAndObserver_h
#define SubjectAndObserver_h

class Subject;

class Observer {
public:
	virtual void update(Subject*) = 0;

	Observer() {}
	~Observer() {};

};





class Subject {
public:

		
		virtual void registerObserver(Observer *observer) = 0;

		virtual void removeObserver(Observer *observer) = 0;

		virtual void notifyObservers() = 0;
};

#endif 
