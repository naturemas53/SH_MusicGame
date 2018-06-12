#pragma once
#include <vector>
#include <map>
#include <string>
#include <functional>

class Note;
class NoteFactory;
struct BpmData;

class MusicScoreIO{

public:

	MusicScoreIO(std::string path);
	~MusicScoreIO();

	bool ImportScore(std::vector<std::function<void(Note*)> >& writeData);

	bool ImportBPM(std::vector<BpmData>& writeData);

private:

	const std::string PATH_;
	std::map<char, NoteFactory* > noteFactorys_;

};