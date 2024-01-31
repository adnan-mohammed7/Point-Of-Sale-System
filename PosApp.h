#ifndef SDDS_POSAPP_H
#define SDDS_POSAPP_H

#include "Item.h"

namespace sdds
{
	//class PosApp
	class PosApp
	{
		char m_filename[128];
		Item* m_Iptr[MAX_NO_ITEMS];
		int m_nptr;
		int menu();
		/*To add new item to the PosApp*/
		void addItem();

		/*To remove selected item from the PosApp*/
		void removeItem();

		/*To restock an item in the PosApp*/
		void stockItem();

		/*To generate list of all the Items stored in PosApp*/
		void listItems(bool total);

		/*Point of sale system function*/
		void POS();

		/*To store all the updates quantites items in the file*/
		void saveRecs() const;

		/*To load all the items from the file into the PosApp*/
		void loadRecs();

		/*Prints the title of action
		Parameters:
		const char* msg*/
		void title(const char* msg)const;

		/*Set the PosApp into safe empty state*/
		void setEmpty();

		/*Prints the header of the list*/
		void printHeader();

		/*Prints all the items stored in PosApp*/
		void printBody();

		/*Calculates and displays the total of all the items*/
		void printTotal();

		/*To get user input for the row number of the item to be removed*/
		int selectItem();

		/*To get sku from the user and return the item address or nullptr*/
		Item* search(char* sku);

	public:
		/*One argument constructor
		Parameters:
		const char filename[]*/
		PosApp(const char filename[]);
		PosApp(PosApp& input) = delete;
		PosApp& operator=(PosApp& input) = delete;
		void run();
		~PosApp();
	};
}

#endif // !POSAPP_H
