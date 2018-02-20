#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>

/*

	This program writes a single MIDI file, intended to be imported to notation software.

*/

#define LINE "---------------------"
#define NAME "By Oliver Getz Rodahl"

using namespace std;

void printHeader()
{
	std::cout << endl << LINE << endl;
	std::cout << NAME << endl;
	std::cout << LINE << endl << endl;
}

void printMidiHeader(std::ofstream &out, int format, int tracks, int ppqn)
{
	//MIDI Header HEX values
	// out << "4d54 6864 "; 	//Header ID - Literally "MThd"
	// out << "0000 0006 "; 	//Length of header after ID (6 bytes).
	// out << "0000 "; 			//Format. Can be 0, 1, or 2.
	// out << "0001 "; 			//How many tracks. If format is 0, this has to be 1.
	// out << "0060 ";			//PPQN (Pulses Per Quarter Note), 96 in this case.

	int bufferSize = 14;		//The size of a header should always be 14.
	char buffer[bufferSize]; 	//Memory allocation for our header string.

	//populate buffer with 0s.
	for (int i=0; i < bufferSize; i++)
	{
		buffer[i] = 0;
	}

	//Copy contents of headerText to buffer
	strcpy(buffer, "MThd");	//Header ID
	buffer[7] = 6; 			//Size of track in bytes. Is always 6 for headers.
	buffer[10] = format; 	//MIDI Format 0, 1, or 2.
	buffer[11]= tracks; 	//Number of tracks. Should always be 1 for format 0;
	buffer[13]= ppqn;		//Pulse per quarter note.

	//Write header to file as hex. The << operators can only print as characters.
	out.write(buffer, bufferSize);
}

void printMidiTrack(std::ofstream &out)
{
	//Hex code reference:
	// out << "4d54 726b "; 	//Header ID - Literally "MTrk"
	// out << "0000 0029 ";		//Length of track in bytes
	// out << "00 ";			//Time since last event
	// out << "c0 49 ",			//Program change 73 - flute
	// out << "00 ";
	// out << "b0 79 00 00 ";	//Reset all controllers
	// out << "b0 40 00 00 ";	//Sustain = 0.
	// out << "b0 5b 34 00 ";	//Reverb = 52.
	// out << "b0 0a 46 00 ";	//Pan = 70.
	// out << "b0 07 5f 00 ";	//Volume = 95.
	// out << "ff 03 05 46 6c 75 74 65 "; //Track name = "Flute"
	// out << "00 ";
	// out << "90 3c 51"; //Note On, Channel 0, Note 60, velocity 81.
	// out << "9e 00 ";
	// out << "80 3c 00 ";//Note off, channel 0, Note 60, velocity 0.
	// out << "01 ";
	// out << "ff 2f 00";

	//Simple MIDI file example
	//4d54 726b 				//Header ID - Literally "MTrk"
	//0000 0022 				//Length of track in bytes
	//00						////Time since last event
	//ff 03 01 00
	//00 
	//ff 58 04 | 04 02 24 08	//Time signature. Time signature. 04 = numerator. 02 = Denominator (02=Q,03=8th,04=16th), 24 = PPQN.
	//00 
	//ff 58 04 | 04 02 24 08
	//00 
	//90 48 64 81 
	//40 80 48 40 
	//00ff 2f00 				//End of Track

	int bufferSize = 42;
	char buffer[bufferSize]; 	//Memory allocation for our header string.

	//populate buffer with 0s.
	for (int i=0; i < bufferSize; i++)
	{
		buffer[i] = 0;
	}

	strcpy(buffer, "MTrk");
	buffer[7] = 34; 			//Size of track in bytes.
	buffer[9] = 0xff;
	buffer[10] = 3;
	buffer[11] = 1;
	buffer[14] = 0xff;
	buffer[15] = 0x58;
	buffer[16] = 0x04;
	buffer[17] = 0x04;
	buffer[18] = 0x02;
	buffer[19] = 0x24;
	buffer[20] = 0x08;
	buffer[22] = 0xff;
	buffer[23] = 0x58;
	buffer[24] = 0x04;
	buffer[25] = 0x04;
	buffer[26] = 0x02;
	buffer[27] = 0x24;
	buffer[28] = 0x08;
	buffer[30] = 0x90;
	buffer[31] = 0x48;
	buffer[32] = 0x64;
	buffer[33] = 0x81;
	buffer[34] = 0x40;
	buffer[35] = 0x80;
	buffer[36] = 0x48;
	buffer[37] = 0x40;
	buffer[39] = 0xff;
	buffer[40] = 0x2f;


	out.write(buffer, bufferSize);
}

int main()
{
	//TODO: Prompt for filename, key, amount of notes,
	string fileName = "myMIDI.mid";

	printHeader();

	ofstream outFile (fileName.c_str(), ios::out | ios::binary); //c_str() must be used when storing the name of the file in a variable/string.

	printMidiHeader(outFile, 0, 1, 96); //Outfile, MIDI format, tracks, PPQN,
	printMidiTrack(outFile);

	outFile.close();

	return 0;
}