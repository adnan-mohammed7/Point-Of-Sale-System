/* Citation and Sources...
Final Project Milestone 1
Module: PosApp
Filename: PosApp.h
Version 1.0
Author	Adnan Mohammed
Revision History
-----------------------------------------------------------
Date      13th March 2023
2023/03/13  Preliminary release
2023/03/13  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#ifndef SDDS_POSAPP_H
#define SDDS_POSAPP_H

namespace sdds
{
	//class PosApp
	class PosApp
	{
		char m_filename[255];
		int menu() const;
		void addItem() const;
		void removeItem() const;
		void stockItem() const;
		void listItems() const;
		void POS() const;
		void saveRecs() const;
		void loadRecs() const;

	public:
		//Default Constructor
		PosApp(const char filename[]);
		PosApp(PosApp& input) = delete;
		PosApp& operator=(PosApp& input) = delete;
		void run() const;
	};
}

#endif // !POSAPP_H
