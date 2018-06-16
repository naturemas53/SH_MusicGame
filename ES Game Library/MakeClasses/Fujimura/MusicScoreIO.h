#pragma once
#include <vector>
#include <map>
#include <string>

class Lane;
class Note;
class NoteFactory;
struct BpmData;

class MusicScoreIO{

public:

	MusicScoreIO(std::string path);
	~MusicScoreIO();

	bool ImportScore(std::vector<Lane*>& writeLane);

	bool ImportBPM(std::vector<BpmData>& writeArray);

private:

	const std::string PATH_;
	std::map<char, NoteFactory* > noteFactorys_;

};