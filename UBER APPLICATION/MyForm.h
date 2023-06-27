
/*

$$$$ V1.3 update $$$$

# problems solved:
* captain doubled appearing in flow panel
* 
* 
* 
*/

// >> console have no importance but to seee what is happening in the background

#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include <thread>
#include <chrono>
#include<string.h>
#include <iomanip>
#include <vector>
#include<ctime>
#include <msclr\marshal_cppstd.h>
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::string;
using std::ifstream;
using std::fstream;

using namespace System;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

// structs//
struct Full_name
{
	string firstname = "", lastname = "";
};

struct Car_info
{
	string SColor;
	string SType;
	string  ILevel;
	string SNumber;
};

struct User_Data
{
	string SID;
	string SUser_name;
	string SPassword;
	string SCity_location;
	Full_name full_name;
};

struct Rider
{
	User_Data user_data;
	string Distination;
	string desired_car_level;
};



struct Captain
{
	string fast_full_name;
	User_Data user_data;
	Car_info car_info;
	float rating = 5.0;
};

struct User //(this will be your data if you sign in or login)
{
	User_Data user_data;

	string role = "C/R"; // rider or captain 

	// if captain
	float rating = 5.0;
	Car_info car;
	// if rider


};

struct Ride
{
	Rider rider;
	Captain captain;
	string name = "NONE";
	string Distination = "NONE";
	string Location = "NONE";
	string Car_level = "NONE";
	string Verdict = "Pending..";
	bool accepted = 0;
	string Sum_time = "D/Y , H:M (A/P)m";

};
//end structs//
Ride Pending_ride;
User Program_user; // the user info
int Riders_count = 0;
int Captains_count = 0;
int rider_history_rides_count = 0;
bool in_a_Ride = 0;
bool making_schedule_ride = 0;
bool is_choosing_a_rate = 0;
string s_hours, s_minutes, s_ampm;









void Get_counts() // get the nimer of stored captains and riders
{
	ifstream data_file("account_info.txt");
	std::vector<string> file_lines;

	string line;
	while (getline(data_file, line))
	{
		if (line.find('#') == string::npos && line.size())
		{
			//8C&4R
			string riders = line.substr(0, line.find('R'));
			string captains = line.substr(line.find('&') + 1, (line.size() - line.find('&') - 2));


			String^ c_riders = gcnew String(riders.c_str());
			String^ c_captains = gcnew String(captains.c_str());


			Riders_count = Int32::Parse(c_riders); // convert from class String to int 
			Captains_count = Int32::Parse(c_captains);

			cout << "**detected " << Captains_count << " Captains and " << Riders_count << " riders**" << endl;

			data_file.close();
			break;
		}
	}
}




bool Check_account(string username, string password)
{
	ifstream userFile("accounts.txt");
	string line;

	while (getline(userFile, line)) // bershama
	{

		std::string storedUsername = line.substr(0, line.find(","));
		std::string storedPassword = line.substr(line.find(",") + 1);

		if (storedUsername == username && storedPassword == password) {
			userFile.close();
			return true;
		}
	}

	userFile.close();
	return false;
}

void Set_user_data_fill(string username, string password)
{
	cout << "flag2" << endl;
	ifstream account_info("account_info.txt");
	cout << "flag3" << endl;
	string data_line;

	string arr[20]{};

	cout << "flag4" << endl;
	while (getline(account_info, data_line))
	{
		// iterating for every line
		string s{};
		int arr_ind = 0;
		for (int i = 0; i < data_line.size(); i++)
		{
			if (data_line[i] == '#')
			{
				arr[arr_ind++] = s;
				s = {};

			}
			else
			{
				s.push_back(data_line[i]);
			}

		}
		cout << "flag5" << endl;
		// checking if the username and password are same
		if (username == arr[0] && password == arr[1])
		{
			cout << "flag6" << endl;
			// filling user struct with account information :D
			
				Program_user.user_data.SUser_name = arr[0];
				Program_user.user_data.SPassword = arr[1];
				cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << ' ' << arr[3] << ' ' << arr[4] << ' ' << arr[5] << endl;
				Program_user.role = arr[2];
				Program_user.user_data.SID = arr[3];
				Program_user.user_data.full_name.firstname = arr[4];
				Program_user.user_data.full_name.lastname = arr[5];
				cout << "detected name from file: " << arr[4] << ' ' << arr[5] << endl;



				cout << "welcome " << arr[4] << ' ' << arr[5] << endl;

				if (Program_user.role == "C")
				{
					Program_user.user_data.SCity_location = arr[6];
					Program_user.car.SColor = arr[7];
					Program_user.car.ILevel = arr[8];
					Program_user.car.SNumber = arr[9];
					Program_user.car.SType = arr[10];
					Program_user.rating = std::stof(arr[11]);
					cout << "Rating : " << Program_user.rating << endl;
				}
				
				return;
	
		
			
			

		}



	}
	cout << "error loading info for : "
		<< username << "from account_info.txt" << endl; //if heppens logic error :(

}




namespace UBERAPPLICATION {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	



	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();



			//my functions
			void Display_captain_Schedule_requests();//
			bool Check_plate_number(string plate);
			void Edit_car_info(string plate, string type, string color, string level);
			bool Check_username(string username, string * error);
			bool Check_firstname(string firstname, string * error);
			bool Check_lastname(string lastname, string * error);
			bool Check_password(string password, string * error);
			bool Check_firstname(string firstname, string * error);
			bool Check_lastname(string lastname, string * error);
			bool Check_password(string password, string * error);
			bool Check_captain_location(string location, string * error);
			bool Check_captain_plate(string plate, string * error); /////////
			bool Check_captain_level(string level, string * error);
			bool Check_captain_color(string color, string * error);
			bool Check_captain_type(string type, string * error);
			void Update_counts(string count);
			void Register_user(string firstname, string lastname, string username, string password, string id, string car_number, string car_level, string car_color, string car_type, string location);
			void Register_user(string firstname, string lastname, string username, string password, string id);
			void Clear_captain_register_boxes();
			void Clear_rider_register_boxes();
			Rider convert_user_to_rider(string level, string location, string distination);
			void set_pending_ride(string level, string location, string distination);
			void set_status_message(string message);
			void OnButton_cancel_Click(Object ^ sender, EventArgs ^ e);
			void Add_to_rider_pending_list(Ride ride);
			void Add_to_rider_schedule_list(Ride ride, string hours, string minutes, string ampm);
			void OnButtonClick(Object ^ sender, EventArgs ^ e);
			void Set_rider_profile();
			void Display_on_captains_list(Captain captain);
			void Search_captains_around(string location);
			void Add_to_history(Ride ride);
			void Change_captain_rating(float rating);
			void View_rider_history();
			void Clear_rider_history();
			bool Check_time(string hours, string minutes, string pm_am);
			void set_captain_status_message(string message);
			void OnButtonClick_rider(Object ^ sender, EventArgs ^ e);
			void Display_on_riders_list(Rider rider);
			void Search_riders_around_me();
			void Change_my_rate(int rating);
			void Remove_from_data(string location, string distination, string time);
			void Change_counts(string new_count);









			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ pn_main;
	protected:

	private: System::Windows::Forms::Panel^ pn_bar;
	protected:

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button3;

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Panel^ pn_start;
	private: System::Windows::Forms::Panel^ pn_GIF;

	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Panel^ pn_GIF2;

	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::PictureBox^ pictureBox4;
	private: System::Windows::Forms::Panel^ pn_login_screan;
	private: System::Windows::Forms::Panel^ pn_login;

	private: System::Windows::Forms::PictureBox^ pictureBox6;
	private: System::Windows::Forms::Panel^ pn_back;



	private: System::Windows::Forms::PictureBox^ pictureBox7;

	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Panel^ panel2;


	private: System::Windows::Forms::Panel^ pn_terms;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Panel^ pn_Register;


	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button10;
	private: System::Windows::Forms::Panel^ pn_riderRe;
	private: System::Windows::Forms::PictureBox^ pictureBox10;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel2;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel5;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel4;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel3;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::Button^ button12;
	private: System::Windows::Forms::Button^ button11;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Panel^ pn_captinRe;
	private: System::Windows::Forms::Button^ button13;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel6;
	private: System::Windows::Forms::TextBox^ textBox9;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel7;
	private: System::Windows::Forms::TextBox^ textBox10;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel8;
	private: System::Windows::Forms::TextBox^ textBox11;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel9;
	private: System::Windows::Forms::TextBox^ textBox12;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel10;
	private: System::Windows::Forms::TextBox^ textBox13;
	private: System::Windows::Forms::PictureBox^ pictureBox11;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel11;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::Button^ button14;

	private: System::Windows::Forms::Label^ label22;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel12;
	private: System::Windows::Forms::ComboBox^ comboBox2;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel13;
	private: System::Windows::Forms::TextBox^ textBox14;
	private: System::Windows::Forms::Label^ label23;

	private: System::Windows::Forms::Panel^ pn_terms2;
	private: System::Windows::Forms::Button^ button15;
	private: System::Windows::Forms::Label^ label24;
	private: System::Windows::Forms::RichTextBox^ richTextBox2;
	private: System::Windows::Forms::Label^ label25;
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox9;
	private: System::Windows::Forms::PictureBox^ pictureBox8;
	private: System::Windows::Forms::Panel^ pn_riderMenu;
private: System::Windows::Forms::Panel^ pn_captainMenu;




	private: System::Windows::Forms::PictureBox^ pictureBox13;
	private: System::Windows::Forms::Panel^ pn_menu_list;
	private: System::Windows::Forms::Label^ label26;
	private: System::Windows::Forms::PictureBox^ pictureBox14;
	private: System::Windows::Forms::Label^ label27;

	private: System::Windows::Forms::Button^ button16;


	private: System::Windows::Forms::Button^ button18;

	private: System::Windows::Forms::Button^ button17;
private: System::Windows::Forms::Panel^ pn_schedule_requests;


	private: System::Windows::Forms::Panel^ pn_carInfo;
	private: System::Windows::Forms::Label^ label30;

	private: System::Windows::Forms::Label^ label28;
	private: System::Windows::Forms::Button^ button19;
	private: System::Windows::Forms::Label^ label35;
	private: System::Windows::Forms::Label^ label34;
	private: System::Windows::Forms::Label^ label33;
	private: System::Windows::Forms::Label^ label32;
	private: System::Windows::Forms::Label^ label31;
	private: System::Windows::Forms::Button^ button21;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::Panel^ pn_riderInfo;
private: System::Windows::Forms::Label^ rider_fullname;



	private: System::Windows::Forms::PictureBox^ pictureBox16;
	private: System::Windows::Forms::PictureBox^ pictureBox17;
	private: System::Windows::Forms::Button^ button25;
	private: System::Windows::Forms::Button^ button24;
	private: System::Windows::Forms::Button^ button23;
	private: System::Windows::Forms::Button^ button22;
	private: System::Windows::Forms::Button^ button27;

	private: System::Windows::Forms::Button^ button26;
	private: System::Windows::Forms::Panel^ pn_viewHistory;
	private: System::Windows::Forms::Panel^ pn_penddingList;
	private: System::Windows::Forms::Panel^ pn_scheduleRide;
	private: System::Windows::Forms::Panel^ pn_requestRide;

	private: System::Windows::Forms::Label^ label38;
	private: System::Windows::Forms::Label^ label41;
	private: System::Windows::Forms::Label^ label40;



	private: System::Windows::Forms::Label^ label46;
	private: System::Windows::Forms::Label^ label47;
	private: System::Windows::Forms::Label^ label42;
	private: System::Windows::Forms::Label^ label45;
	private: System::Windows::Forms::Label^ label43;
	private: System::Windows::Forms::Label^ label44;
	private: System::Windows::Forms::Label^ label29;
	private: System::Windows::Forms::Label^ label51;
	private: System::Windows::Forms::Label^ label50;
	private: System::Windows::Forms::Label^ label49;
	private: System::Windows::Forms::Label^ label48;



	private: System::Windows::Forms::Label^ label39;

	private: System::Windows::Forms::ComboBox^ comboBox4;
	private: System::Windows::Forms::ComboBox^ comboBox3;
	private: System::Windows::Forms::Label^ label54;
	private: System::Windows::Forms::Label^ label53;



	private: System::Windows::Forms::Button^ button20;
	private: System::Windows::Forms::PictureBox^ pictureBox18;
	private: System::Windows::Forms::Panel^ pn_captains_around;



	private: System::Windows::Forms::Label^ label56;


	private: System::Windows::Forms::PictureBox^ pictureBox19;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Button^ button29;
	private: System::Windows::Forms::TextBox^ textBox16;
	private: System::Windows::Forms::TextBox^ textBox15;
	private: System::Windows::Forms::ComboBox^ comboBox5;
	private: System::Windows::Forms::ComboBox^ comboBox7;
	private: System::Windows::Forms::ComboBox^ comboBox6;
	private: System::Windows::Forms::Label^ label63;
	private: System::Windows::Forms::Label^ label62;
	private: System::Windows::Forms::Label^ label57;
	private: System::Windows::Forms::Label^ label58;
	private: System::Windows::Forms::Label^ label61;
	private: System::Windows::Forms::Label^ label59;
	private: System::Windows::Forms::Label^ label60;
	private: System::Windows::Forms::PictureBox^ pictureBox20;

	private: System::Windows::Forms::ComboBox^ comboBox8;
	private: System::Windows::Forms::ComboBox^ comboBox9;
	private: System::Windows::Forms::TextBox^ textBox18;
	private: System::Windows::Forms::PictureBox^ pictureBox21;
	private: System::Windows::Forms::Timer^ timer2;



	private: System::Windows::Forms::Label^ label64;
	private: System::Windows::Forms::PictureBox^ pictureBox5;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::PictureBox^ pictureBox22;
	private: System::Windows::Forms::Label^ label65;
	private: System::Windows::Forms::Panel^ pn_profile;
	private: System::Windows::Forms::Button^ button30;
	private: System::Windows::Forms::Label^ label67;
	private: System::Windows::Forms::Label^ label66;
	private: System::Windows::Forms::Label^ label68;
	private: System::Windows::Forms::Label^ label71;
	private: System::Windows::Forms::Label^ label72;
	private: System::Windows::Forms::Label^ label70;
	private: System::Windows::Forms::Label^ label69;
	private: System::Windows::Forms::ComboBox^ comboBox10;
	private: System::Windows::Forms::Button^ button31;
	private: System::Windows::Forms::Label^ label_error;

	private: System::Windows::Forms::PictureBox^ pictureBox25;
	private: System::Windows::Forms::PictureBox^ pictureBox24;
	private: System::Windows::Forms::PictureBox^ pictureBox23;
	private: System::Windows::Forms::Panel^ pn_status;
private: System::Windows::Forms::FlowLayoutPanel^ fpn_schedule_requests;

	private: System::Windows::Forms::Label^ label76;
	private: System::Windows::Forms::Label^ label75;
	private: System::Windows::Forms::Label^ label74;
	private: System::Windows::Forms::Label^ label79;
	private: System::Windows::Forms::Label^ label78;
	private: System::Windows::Forms::Label^ label77;
	private: System::Windows::Forms::PictureBox^ pictureBox26;
	private: System::Windows::Forms::PictureBox^ pictureBox12;
private: System::Windows::Forms::Label^ captain_clock;

	private: System::Windows::Forms::Label^ label80;
	private: System::Windows::Forms::Timer^ clock;







	private: System::Windows::Forms::Timer^ status_timer;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel14;
	private: System::Windows::Forms::ComboBox^ comboBox11;
	private: System::Windows::Forms::Label^ label73;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel15;
	private: System::Windows::Forms::ComboBox^ comboBox12;
	private: System::Windows::Forms::Label^ captain_r_error;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::Label^ rider_r_error;
	private: System::Windows::Forms::ProgressBar^ progressBar2;
	private: System::Windows::Forms::PictureBox^ loading_gifr;

	private: System::Windows::Forms::Timer^ loading_timer;
	private: System::Windows::Forms::PictureBox^ loading_gifc;
private: System::Windows::Forms::Button^ btn_rider_profile;

	private: System::Windows::Forms::Label^ label36;
	private: System::Windows::Forms::ComboBox^ comboBox13;
	private: System::Windows::Forms::Label^ req_error;
	private: System::Windows::Forms::Label^ rider_clock;
	private: System::Windows::Forms::Label^ label55;
	private: System::Windows::Forms::FlowLayoutPanel^ fpn_rider_status;
	private: System::Windows::Forms::Panel^ status_panel;

	private: System::Windows::Forms::Label^ status_message;

	private: System::Windows::Forms::FlowLayoutPanel^ fpn_captains_around;








	private: System::Windows::Forms::PictureBox^ pictureBox27;
	private: System::Windows::Forms::PictureBox^ pictureBox28;
	private: System::Windows::Forms::PictureBox^ pictureBox29;
	private: System::Windows::Forms::Button^ refresh_captains;
	private: System::Windows::Forms::FlowLayoutPanel^ fpn_pendingList;

	private: System::Windows::Forms::Timer^ refreshing_timer;
	private: System::Windows::Forms::PictureBox^ refresh_anim;











private: System::Windows::Forms::Timer^ Ride_timer;
private: System::Windows::Forms::Panel^ pn_rate_captain;
private: System::Windows::Forms::ComboBox^ comboBox14;
private: System::Windows::Forms::Label^ label96;
private: System::Windows::Forms::Label^ label95;
private: System::Windows::Forms::Button^ btn_ok;
private: System::Windows::Forms::Label^ rating_error;
private: System::Windows::Forms::Button^ btn_clear_rider_history;

private: System::Windows::Forms::FlowLayoutPanel^ fpn_rider_history;










private: System::Windows::Forms::Label^ total_rides;
private: System::Windows::Forms::PictureBox^ pictureBox30;
private: System::Windows::Forms::PictureBox^ pictureBox31;
private: System::Windows::Forms::Panel^ panel5;
private: System::Windows::Forms::Panel^ panel6;


private: System::Windows::Forms::Panel^ pn_rider_profile;
private: System::Windows::Forms::PictureBox^ pictureBox32;
private: System::Windows::Forms::Label^ label103;
private: System::Windows::Forms::Label^ label105;
private: System::Windows::Forms::Label^ label106;
private: System::Windows::Forms::Label^ label107;
private: System::Windows::Forms::Label^ label108;
private: System::Windows::Forms::Label^ label114;
private: System::Windows::Forms::Label^ label116;
private: System::Windows::Forms::Label^ label117;
private: System::Windows::Forms::Label^ label118;
private: System::Windows::Forms::Button^ btn_schedule_list;
private: System::Windows::Forms::Button^ btn_save;
private: System::Windows::Forms::ComboBox^ _ampm;
private: System::Windows::Forms::Label^ label104;
private: System::Windows::Forms::Panel^ pn_rider_schedule_list;
private: System::Windows::Forms::Label^ label109;
private: System::Windows::Forms::FlowLayoutPanel^ fpn_rider_schedule_list;









private: System::Windows::Forms::Timer^ check_schedule_timer;
private: System::Windows::Forms::Panel^ pn_search_riders;
private: System::Windows::Forms::Button^ button32;


private: System::Windows::Forms::PictureBox^ search_anim;
private: System::Windows::Forms::FlowLayoutPanel^ fpn_riders_around;










private: System::Windows::Forms::Label^ label93;
private: System::Windows::Forms::PictureBox^ pictureBox36;
private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel16;
private: System::Windows::Forms::Panel^ rider_status_panel;

private: System::Windows::Forms::Label^ label37;
private: System::Windows::Forms::PictureBox^ pictureBox15;
private: System::Windows::Forms::PictureBox^ pictureBox33;
private: System::Windows::Forms::PictureBox^ pictureBox34;
private: System::Windows::Forms::Button^ btn_search;
private: System::Windows::Forms::Timer^ rider_search_timer;
private: System::Windows::Forms::PictureBox^ pictureBox35;
private: System::Windows::Forms::Panel^ panel3;
private: System::Windows::Forms::Panel^ panel7;































	private: System::ComponentModel::IContainer^ components;

















	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		


		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->pn_main = (gcnew System::Windows::Forms::Panel());
			this->pn_riderMenu = (gcnew System::Windows::Forms::Panel());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->pn_requestRide = (gcnew System::Windows::Forms::Panel());
			this->req_error = (gcnew System::Windows::Forms::Label());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->comboBox13 = (gcnew System::Windows::Forms::ComboBox());
			this->button20 = (gcnew System::Windows::Forms::Button());
			this->comboBox4 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->label54 = (gcnew System::Windows::Forms::Label());
			this->label53 = (gcnew System::Windows::Forms::Label());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->pn_captains_around = (gcnew System::Windows::Forms::Panel());
			this->refresh_captains = (gcnew System::Windows::Forms::Button());
			this->refresh_anim = (gcnew System::Windows::Forms::PictureBox());
			this->fpn_captains_around = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label56 = (gcnew System::Windows::Forms::Label());
			this->pictureBox18 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_scheduleRide = (gcnew System::Windows::Forms::Panel());
			this->label104 = (gcnew System::Windows::Forms::Label());
			this->_ampm = (gcnew System::Windows::Forms::ComboBox());
			this->btn_save = (gcnew System::Windows::Forms::Button());
			this->button29 = (gcnew System::Windows::Forms::Button());
			this->textBox16 = (gcnew System::Windows::Forms::TextBox());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox5 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox7 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox6 = (gcnew System::Windows::Forms::ComboBox());
			this->label63 = (gcnew System::Windows::Forms::Label());
			this->label62 = (gcnew System::Windows::Forms::Label());
			this->label57 = (gcnew System::Windows::Forms::Label());
			this->label58 = (gcnew System::Windows::Forms::Label());
			this->label61 = (gcnew System::Windows::Forms::Label());
			this->label59 = (gcnew System::Windows::Forms::Label());
			this->label60 = (gcnew System::Windows::Forms::Label());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->pn_viewHistory = (gcnew System::Windows::Forms::Panel());
			this->total_rides = (gcnew System::Windows::Forms::Label());
			this->btn_clear_rider_history = (gcnew System::Windows::Forms::Button());
			this->fpn_rider_history = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->pictureBox19 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_rate_captain = (gcnew System::Windows::Forms::Panel());
			this->pictureBox30 = (gcnew System::Windows::Forms::PictureBox());
			this->rating_error = (gcnew System::Windows::Forms::Label());
			this->btn_ok = (gcnew System::Windows::Forms::Button());
			this->comboBox14 = (gcnew System::Windows::Forms::ComboBox());
			this->label96 = (gcnew System::Windows::Forms::Label());
			this->label95 = (gcnew System::Windows::Forms::Label());
			this->pictureBox31 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_penddingList = (gcnew System::Windows::Forms::Panel());
			this->fpn_pendingList = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pictureBox20 = (gcnew System::Windows::Forms::PictureBox());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->pictureBox17 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_rider_schedule_list = (gcnew System::Windows::Forms::Panel());
			this->label109 = (gcnew System::Windows::Forms::Label());
			this->fpn_rider_schedule_list = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pn_rider_profile = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->pictureBox32 = (gcnew System::Windows::Forms::PictureBox());
			this->label103 = (gcnew System::Windows::Forms::Label());
			this->label105 = (gcnew System::Windows::Forms::Label());
			this->label106 = (gcnew System::Windows::Forms::Label());
			this->label107 = (gcnew System::Windows::Forms::Label());
			this->label108 = (gcnew System::Windows::Forms::Label());
			this->label114 = (gcnew System::Windows::Forms::Label());
			this->label116 = (gcnew System::Windows::Forms::Label());
			this->label117 = (gcnew System::Windows::Forms::Label());
			this->label118 = (gcnew System::Windows::Forms::Label());
			this->fpn_rider_status = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->status_panel = (gcnew System::Windows::Forms::Panel());
			this->status_message = (gcnew System::Windows::Forms::Label());
			this->pictureBox29 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox27 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox28 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_riderInfo = (gcnew System::Windows::Forms::Panel());
			this->btn_schedule_list = (gcnew System::Windows::Forms::Button());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->rider_fullname = (gcnew System::Windows::Forms::Label());
			this->rider_clock = (gcnew System::Windows::Forms::Label());
			this->label55 = (gcnew System::Windows::Forms::Label());
			this->btn_rider_profile = (gcnew System::Windows::Forms::Button());
			this->button27 = (gcnew System::Windows::Forms::Button());
			this->button26 = (gcnew System::Windows::Forms::Button());
			this->button25 = (gcnew System::Windows::Forms::Button());
			this->button24 = (gcnew System::Windows::Forms::Button());
			this->button23 = (gcnew System::Windows::Forms::Button());
			this->button22 = (gcnew System::Windows::Forms::Button());
			this->pictureBox16 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_captainMenu = (gcnew System::Windows::Forms::Panel());
			this->pn_search_riders = (gcnew System::Windows::Forms::Panel());
			this->button32 = (gcnew System::Windows::Forms::Button());
			this->search_anim = (gcnew System::Windows::Forms::PictureBox());
			this->fpn_riders_around = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label93 = (gcnew System::Windows::Forms::Label());
			this->pictureBox36 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_carInfo = (gcnew System::Windows::Forms::Panel());
			this->label_error = (gcnew System::Windows::Forms::Label());
			this->button31 = (gcnew System::Windows::Forms::Button());
			this->comboBox10 = (gcnew System::Windows::Forms::ComboBox());
			this->label71 = (gcnew System::Windows::Forms::Label());
			this->label72 = (gcnew System::Windows::Forms::Label());
			this->label70 = (gcnew System::Windows::Forms::Label());
			this->label69 = (gcnew System::Windows::Forms::Label());
			this->comboBox8 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox9 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox18 = (gcnew System::Windows::Forms::TextBox());
			this->label51 = (gcnew System::Windows::Forms::Label());
			this->label50 = (gcnew System::Windows::Forms::Label());
			this->label49 = (gcnew System::Windows::Forms::Label());
			this->label48 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->label47 = (gcnew System::Windows::Forms::Label());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->label44 = (gcnew System::Windows::Forms::Label());
			this->pictureBox35 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox13 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_schedule_requests = (gcnew System::Windows::Forms::Panel());
			this->fpn_schedule_requests = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->pn_profile = (gcnew System::Windows::Forms::Panel());
			this->panel7 = (gcnew System::Windows::Forms::Panel());
			this->pictureBox26 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox12 = (gcnew System::Windows::Forms::PictureBox());
			this->label76 = (gcnew System::Windows::Forms::Label());
			this->label75 = (gcnew System::Windows::Forms::Label());
			this->label74 = (gcnew System::Windows::Forms::Label());
			this->label68 = (gcnew System::Windows::Forms::Label());
			this->label67 = (gcnew System::Windows::Forms::Label());
			this->label66 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->label79 = (gcnew System::Windows::Forms::Label());
			this->label78 = (gcnew System::Windows::Forms::Label());
			this->label77 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->pn_status = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel16 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->rider_status_panel = (gcnew System::Windows::Forms::Panel());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->pictureBox15 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox33 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox34 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_menu_list = (gcnew System::Windows::Forms::Panel());
			this->btn_search = (gcnew System::Windows::Forms::Button());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->label65 = (gcnew System::Windows::Forms::Label());
			this->captain_clock = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label80 = (gcnew System::Windows::Forms::Label());
			this->button30 = (gcnew System::Windows::Forms::Button());
			this->button19 = (gcnew System::Windows::Forms::Button());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->pictureBox14 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_login_screan = (gcnew System::Windows::Forms::Panel());
			this->pn_login = (gcnew System::Windows::Forms::Panel());
			this->pictureBox25 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox24 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox23 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->label64 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_back = (gcnew System::Windows::Forms::Panel());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->pictureBox22 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_riderRe = (gcnew System::Windows::Forms::Panel());
			this->loading_gifr = (gcnew System::Windows::Forms::PictureBox());
			this->progressBar2 = (gcnew System::Windows::Forms::ProgressBar());
			this->rider_r_error = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel5 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel4 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel3 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox10 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_captinRe = (gcnew System::Windows::Forms::Panel());
			this->loading_gifc = (gcnew System::Windows::Forms::PictureBox());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->captain_r_error = (gcnew System::Windows::Forms::Label());
			this->label73 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->flowLayoutPanel13 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel15 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->flowLayoutPanel14 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->flowLayoutPanel12 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->comboBox12 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox11 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->flowLayoutPanel11 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel6 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel7 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel8 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel9 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel10 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox11 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_terms = (gcnew System::Windows::Forms::Panel());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->pn_terms2 = (gcnew System::Windows::Forms::Panel());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
			this->pn_Register = (gcnew System::Windows::Forms::Panel());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_start = (gcnew System::Windows::Forms::Panel());
			this->pn_GIF = (gcnew System::Windows::Forms::Panel());
			this->button21 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_GIF2 = (gcnew System::Windows::Forms::Panel());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pn_bar = (gcnew System::Windows::Forms::Panel());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox21 = (gcnew System::Windows::Forms::PictureBox());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->clock = (gcnew System::Windows::Forms::Timer(this->components));
			this->status_timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->loading_timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->refreshing_timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->Ride_timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->check_schedule_timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->rider_search_timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->pn_main->SuspendLayout();
			this->pn_riderMenu->SuspendLayout();
			this->panel4->SuspendLayout();
			this->pn_requestRide->SuspendLayout();
			this->pn_captains_around->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->refresh_anim))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox18))->BeginInit();
			this->pn_scheduleRide->SuspendLayout();
			this->pn_viewHistory->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox19))->BeginInit();
			this->pn_rate_captain->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox30))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox31))->BeginInit();
			this->pn_penddingList->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox20))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox17))->BeginInit();
			this->pn_rider_schedule_list->SuspendLayout();
			this->pn_rider_profile->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox32))->BeginInit();
			this->fpn_rider_status->SuspendLayout();
			this->status_panel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox29))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox27))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox28))->BeginInit();
			this->pn_riderInfo->SuspendLayout();
			this->panel5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox16))->BeginInit();
			this->pn_captainMenu->SuspendLayout();
			this->pn_search_riders->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->search_anim))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox36))->BeginInit();
			this->pn_carInfo->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox35))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->BeginInit();
			this->pn_schedule_requests->SuspendLayout();
			this->pn_profile->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox26))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->BeginInit();
			this->pn_status->SuspendLayout();
			this->flowLayoutPanel16->SuspendLayout();
			this->rider_status_panel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox15))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox33))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox34))->BeginInit();
			this->pn_menu_list->SuspendLayout();
			this->panel6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox14))->BeginInit();
			this->pn_login_screan->SuspendLayout();
			this->pn_login->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox25))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox24))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox23))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			this->pn_back->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox22))->BeginInit();
			this->pn_riderRe->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->loading_gifr))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->BeginInit();
			this->pn_captinRe->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->loading_gifc))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->BeginInit();
			this->pn_terms->SuspendLayout();
			this->pn_terms2->SuspendLayout();
			this->pn_Register->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			this->pn_start->SuspendLayout();
			this->pn_GIF->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->pn_GIF2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->pn_bar->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox21))->BeginInit();
			this->SuspendLayout();
			// 
			// pn_main
			// 
			this->pn_main->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pn_main->Controls->Add(this->pn_riderMenu);
			this->pn_main->Controls->Add(this->pn_captainMenu);
			this->pn_main->Controls->Add(this->pn_login_screan);
			this->pn_main->Controls->Add(this->pn_riderRe);
			this->pn_main->Controls->Add(this->pn_captinRe);
			this->pn_main->Controls->Add(this->pn_terms);
			this->pn_main->Controls->Add(this->pn_terms2);
			this->pn_main->Controls->Add(this->pn_Register);
			this->pn_main->Controls->Add(this->pn_start);
			this->pn_main->Controls->Add(this->pn_bar);
			this->pn_main->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_main->Location = System::Drawing::Point(0, 0);
			this->pn_main->Margin = System::Windows::Forms::Padding(2);
			this->pn_main->Name = L"pn_main";
			this->pn_main->Size = System::Drawing::Size(928, 528);
			this->pn_main->TabIndex = 0;
			// 
			// pn_riderMenu
			// 
			this->pn_riderMenu->Controls->Add(this->panel4);
			this->pn_riderMenu->Controls->Add(this->pn_riderInfo);
			this->pn_riderMenu->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_riderMenu->Location = System::Drawing::Point(0, 34);
			this->pn_riderMenu->Margin = System::Windows::Forms::Padding(2);
			this->pn_riderMenu->Name = L"pn_riderMenu";
			this->pn_riderMenu->Size = System::Drawing::Size(928, 494);
			this->pn_riderMenu->TabIndex = 2;
			// 
			// panel4
			// 
			this->panel4->Controls->Add(this->pn_captains_around);
			this->panel4->Controls->Add(this->pn_requestRide);
			this->panel4->Controls->Add(this->pn_scheduleRide);
			this->panel4->Controls->Add(this->pn_viewHistory);
			this->panel4->Controls->Add(this->pictureBox19);
			this->panel4->Controls->Add(this->pn_rate_captain);
			this->panel4->Controls->Add(this->pn_penddingList);
			this->panel4->Controls->Add(this->pictureBox17);
			this->panel4->Controls->Add(this->pn_rider_schedule_list);
			this->panel4->Controls->Add(this->pn_rider_profile);
			this->panel4->Controls->Add(this->fpn_rider_status);
			this->panel4->Location = System::Drawing::Point(0, 0);
			this->panel4->Margin = System::Windows::Forms::Padding(2);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(712, 494);
			this->panel4->TabIndex = 1;
			// 
			// pn_requestRide
			// 
			this->pn_requestRide->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pn_requestRide.BackgroundImage")));
			this->pn_requestRide->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pn_requestRide->Controls->Add(this->req_error);
			this->pn_requestRide->Controls->Add(this->label36);
			this->pn_requestRide->Controls->Add(this->comboBox13);
			this->pn_requestRide->Controls->Add(this->button20);
			this->pn_requestRide->Controls->Add(this->comboBox4);
			this->pn_requestRide->Controls->Add(this->comboBox3);
			this->pn_requestRide->Controls->Add(this->label54);
			this->pn_requestRide->Controls->Add(this->label53);
			this->pn_requestRide->Controls->Add(this->label41);
			this->pn_requestRide->Location = System::Drawing::Point(0, 0);
			this->pn_requestRide->Margin = System::Windows::Forms::Padding(2);
			this->pn_requestRide->Name = L"pn_requestRide";
			this->pn_requestRide->Size = System::Drawing::Size(713, 437);
			this->pn_requestRide->TabIndex = 1;
			// 
			// req_error
			// 
			this->req_error->AutoSize = true;
			this->req_error->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->req_error->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->req_error->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->req_error->Location = System::Drawing::Point(265, 335);
			this->req_error->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->req_error->Name = L"req_error";
			this->req_error->Size = System::Drawing::Size(44, 17);
			this->req_error->TabIndex = 50;
			this->req_error->Text = L"error";
			this->req_error->Visible = false;
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->label36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label36->Location = System::Drawing::Point(219, 147);
			this->label36->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(83, 20);
			this->label36->TabIndex = 49;
			this->label36->Text = L"Car level:";
			// 
			// comboBox13
			// 
			this->comboBox13->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox13->FormattingEnabled = true;
			this->comboBox13->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Level 1", L"Level 2", L"Level 3" });
			this->comboBox13->Location = System::Drawing::Point(311, 146);
			this->comboBox13->Margin = System::Windows::Forms::Padding(2);
			this->comboBox13->Name = L"comboBox13";
			this->comboBox13->Size = System::Drawing::Size(158, 21);
			this->comboBox13->TabIndex = 48;
			this->comboBox13->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox13_SelectedIndexChanged);
			// 
			// button20
			// 
			this->button20->BackColor = System::Drawing::Color::DarkCyan;
			this->button20->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button20->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button20->Location = System::Drawing::Point(262, 368);
			this->button20->Margin = System::Windows::Forms::Padding(2);
			this->button20->Name = L"button20";
			this->button20->Size = System::Drawing::Size(201, 42);
			this->button20->TabIndex = 47;
			this->button20->Text = L"Next";
			this->button20->UseVisualStyleBackColor = false;
			this->button20->Click += gcnew System::EventHandler(this, &MyForm::button20_Click);
			// 
			// comboBox4
			// 
			this->comboBox4->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox4->FormattingEnabled = true;
			this->comboBox4->Items->AddRange(gcnew cli::array< System::Object^  >(34) {
				L"Cairo", L"Alexandria", L"Giza", L"Qalyubia",
					L"Port Said", L"Suez", L"Luxor", L"El Mansura", L"El Mahalla El Kubra", L"Tanta", L"Ismailia", L"Assiut", L"Fayoum", L"Zagazig",
					L"Aswan", L"Damietta", L"Damanhur", L"El Minya", L"Beni Suef", L"Qena", L"Sohag", L"Hurghada", L"Marsa Matruh", L"Arish", L"Banha",
					L"Kafr El Sheikh", L"Idfu", L"Shibin El Kom", L"Minya", L"Beheira", L"Daqahliya", L"North Sinai", L"Red Sea", L"Sharqiya"
			});
			this->comboBox4->Location = System::Drawing::Point(311, 93);
			this->comboBox4->Margin = System::Windows::Forms::Padding(2);
			this->comboBox4->Name = L"comboBox4";
			this->comboBox4->Size = System::Drawing::Size(158, 21);
			this->comboBox4->TabIndex = 3;
			// 
			// comboBox3
			// 
			this->comboBox3->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(34) {
				L"Cairo", L"Alexandria", L"Giza", L"Qalyubia",
					L"Port Said", L"Suez", L"Luxor", L"El Mansura", L"El Mahalla El Kubra", L"Tanta", L"Ismailia", L"Assiut", L"Fayoum", L"Zagazig",
					L"Aswan", L"Damietta", L"Damanhur", L"El Minya", L"Beni Suef", L"Qena", L"Sohag", L"Hurghada", L"Marsa Matruh", L"Arish", L"Banha",
					L"Kafr El Sheikh", L"Idfu", L"Shibin El Kom", L"Minya", L"Beheira", L"Daqahliya", L"North Sinai", L"Red Sea", L"Sharqiya"
			});
			this->comboBox3->Location = System::Drawing::Point(311, 46);
			this->comboBox3->Margin = System::Windows::Forms::Padding(2);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(158, 21);
			this->comboBox3->TabIndex = 3;
			// 
			// label54
			// 
			this->label54->AutoSize = true;
			this->label54->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->label54->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label54->Location = System::Drawing::Point(219, 94);
			this->label54->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label54->Name = L"label54";
			this->label54->Size = System::Drawing::Size(39, 20);
			this->label54->TabIndex = 2;
			this->label54->Text = L"To :";
			// 
			// label53
			// 
			this->label53->AutoSize = true;
			this->label53->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->label53->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label53->Location = System::Drawing::Point(213, 44);
			this->label53->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label53->Name = L"label53";
			this->label53->Size = System::Drawing::Size(60, 20);
			this->label53->TabIndex = 2;
			this->label53->Text = L"From :";
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->label41->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label41->Location = System::Drawing::Point(268, 0);
			this->label41->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(193, 29);
			this->label41->TabIndex = 0;
			this->label41->Text = L"Request a Ride";
			// 
			// pn_captains_around
			// 
			this->pn_captains_around->Controls->Add(this->refresh_captains);
			this->pn_captains_around->Controls->Add(this->refresh_anim);
			this->pn_captains_around->Controls->Add(this->fpn_captains_around);
			this->pn_captains_around->Controls->Add(this->label56);
			this->pn_captains_around->Controls->Add(this->pictureBox18);
			this->pn_captains_around->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_captains_around->Location = System::Drawing::Point(0, 0);
			this->pn_captains_around->Margin = System::Windows::Forms::Padding(2);
			this->pn_captains_around->Name = L"pn_captains_around";
			this->pn_captains_around->Size = System::Drawing::Size(712, 435);
			this->pn_captains_around->TabIndex = 49;
			this->pn_captains_around->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_captains_around_Paint);
			// 
			// refresh_captains
			// 
			this->refresh_captains->Cursor = System::Windows::Forms::Cursors::Hand;
			this->refresh_captains->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->refresh_captains->Location = System::Drawing::Point(206, 386);
			this->refresh_captains->Name = L"refresh_captains";
			this->refresh_captains->Size = System::Drawing::Size(104, 31);
			this->refresh_captains->TabIndex = 53;
			this->refresh_captains->Text = L"Refresh";
			this->refresh_captains->UseVisualStyleBackColor = true;
			this->refresh_captains->Click += gcnew System::EventHandler(this, &MyForm::refresh_captains_Click);
			// 
			// refresh_anim
			// 
			this->refresh_anim->Cursor = System::Windows::Forms::Cursors::Hand;
			this->refresh_anim->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"refresh_anim.Image")));
			this->refresh_anim->Location = System::Drawing::Point(172, 387);
			this->refresh_anim->Margin = System::Windows::Forms::Padding(2);
			this->refresh_anim->Name = L"refresh_anim";
			this->refresh_anim->Size = System::Drawing::Size(34, 31);
			this->refresh_anim->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->refresh_anim->TabIndex = 3;
			this->refresh_anim->TabStop = false;
			this->refresh_anim->Visible = false;
			// 
			// fpn_captains_around
			// 
			this->fpn_captains_around->AutoScroll = true;
			this->fpn_captains_around->Location = System::Drawing::Point(5, 42);
			this->fpn_captains_around->Name = L"fpn_captains_around";
			this->fpn_captains_around->Padding = System::Windows::Forms::Padding(5);
			this->fpn_captains_around->Size = System::Drawing::Size(318, 338);
			this->fpn_captains_around->TabIndex = 52;
			// 
			// label56
			// 
			this->label56->AutoSize = true;
			this->label56->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label56->Location = System::Drawing::Point(59, 15);
			this->label56->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label56->Name = L"label56";
			this->label56->Size = System::Drawing::Size(184, 20);
			this->label56->TabIndex = 50;
			this->label56->Text = L"Captains around you :";
			// 
			// pictureBox18
			// 
			this->pictureBox18->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox18.Image")));
			this->pictureBox18->Location = System::Drawing::Point(0, 0);
			this->pictureBox18->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox18->Name = L"pictureBox18";
			this->pictureBox18->Size = System::Drawing::Size(712, 437);
			this->pictureBox18->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox18->TabIndex = 48;
			this->pictureBox18->TabStop = false;
			// 
			// pn_scheduleRide
			// 
			this->pn_scheduleRide->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pn_scheduleRide.BackgroundImage")));
			this->pn_scheduleRide->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pn_scheduleRide->Controls->Add(this->label104);
			this->pn_scheduleRide->Controls->Add(this->_ampm);
			this->pn_scheduleRide->Controls->Add(this->btn_save);
			this->pn_scheduleRide->Controls->Add(this->button29);
			this->pn_scheduleRide->Controls->Add(this->textBox16);
			this->pn_scheduleRide->Controls->Add(this->textBox15);
			this->pn_scheduleRide->Controls->Add(this->comboBox5);
			this->pn_scheduleRide->Controls->Add(this->comboBox7);
			this->pn_scheduleRide->Controls->Add(this->comboBox6);
			this->pn_scheduleRide->Controls->Add(this->label63);
			this->pn_scheduleRide->Controls->Add(this->label62);
			this->pn_scheduleRide->Controls->Add(this->label57);
			this->pn_scheduleRide->Controls->Add(this->label58);
			this->pn_scheduleRide->Controls->Add(this->label61);
			this->pn_scheduleRide->Controls->Add(this->label59);
			this->pn_scheduleRide->Controls->Add(this->label60);
			this->pn_scheduleRide->Controls->Add(this->label40);
			this->pn_scheduleRide->Location = System::Drawing::Point(0, 0);
			this->pn_scheduleRide->Margin = System::Windows::Forms::Padding(2);
			this->pn_scheduleRide->Name = L"pn_scheduleRide";
			this->pn_scheduleRide->Size = System::Drawing::Size(713, 439);
			this->pn_scheduleRide->TabIndex = 0;
			// 
			// label104
			// 
			this->label104->AutoSize = true;
			this->label104->BackColor = System::Drawing::Color::LightSkyBlue;
			this->label104->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->label104->ForeColor = System::Drawing::Color::Red;
			this->label104->Location = System::Drawing::Point(97, 375);
			this->label104->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label104->Name = L"label104";
			this->label104->Size = System::Drawing::Size(44, 17);
			this->label104->TabIndex = 59;
			this->label104->Text = L"error";
			this->label104->Visible = false;
			// 
			// _ampm
			// 
			this->_ampm->BackColor = System::Drawing::Color::Azure;
			this->_ampm->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->_ampm->FormattingEnabled = true;
			this->_ampm->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"AM", L"PM" });
			this->_ampm->Location = System::Drawing::Point(568, 331);
			this->_ampm->Margin = System::Windows::Forms::Padding(2);
			this->_ampm->Name = L"_ampm";
			this->_ampm->Size = System::Drawing::Size(110, 21);
			this->_ampm->TabIndex = 58;
			// 
			// btn_save
			// 
			this->btn_save->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(82)), static_cast<System::Int32>(static_cast<System::Byte>(126)),
				static_cast<System::Int32>(static_cast<System::Byte>(207)));
			this->btn_save->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btn_save->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->btn_save->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_save->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Bold));
			this->btn_save->ForeColor = System::Drawing::SystemColors::Control;
			this->btn_save->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_save->Location = System::Drawing::Point(556, 395);
			this->btn_save->Margin = System::Windows::Forms::Padding(2);
			this->btn_save->Name = L"btn_save";
			this->btn_save->Size = System::Drawing::Size(151, 38);
			this->btn_save->TabIndex = 57;
			this->btn_save->Text = L"Save";
			this->btn_save->UseVisualStyleBackColor = false;
			this->btn_save->Click += gcnew System::EventHandler(this, &MyForm::btn_save_Click);
			// 
			// button29
			// 
			this->button29->BackColor = System::Drawing::Color::WhiteSmoke;
			this->button29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button29->Location = System::Drawing::Point(275, 453);
			this->button29->Margin = System::Windows::Forms::Padding(2);
			this->button29->Name = L"button29";
			this->button29->Size = System::Drawing::Size(159, 34);
			this->button29->TabIndex = 56;
			this->button29->Text = L"Save";
			this->button29->UseVisualStyleBackColor = false;
			this->button29->Click += gcnew System::EventHandler(this, &MyForm::button29_Click);
			// 
			// textBox16
			// 
			this->textBox16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox16->Location = System::Drawing::Point(441, 329);
			this->textBox16->Margin = System::Windows::Forms::Padding(2);
			this->textBox16->Multiline = true;
			this->textBox16->Name = L"textBox16";
			this->textBox16->Size = System::Drawing::Size(76, 24);
			this->textBox16->TabIndex = 55;
			// 
			// textBox15
			// 
			this->textBox15->BackColor = System::Drawing::Color::White;
			this->textBox15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox15->Location = System::Drawing::Point(202, 328);
			this->textBox15->Margin = System::Windows::Forms::Padding(2);
			this->textBox15->Multiline = true;
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(76, 25);
			this->textBox15->TabIndex = 54;
			// 
			// comboBox5
			// 
			this->comboBox5->BackColor = System::Drawing::Color::Azure;
			this->comboBox5->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox5->FormattingEnabled = true;
			this->comboBox5->Items->AddRange(gcnew cli::array< System::Object^  >(34) {
				L"Cairo", L"Alexandria", L"Giza", L"Qalyubia",
					L"Port Said", L"Suez", L"Luxor", L"El Mansura", L"El Mahalla El Kubra", L"Tanta", L"Ismailia", L"Assiut", L"Fayoum", L"Zagazig",
					L"Aswan", L"Damietta", L"Damanhur", L"El Minya", L"Beni Suef", L"Qena", L"Sohag", L"Hurghada", L"Marsa Matruh", L"Arish", L"Banha",
					L"Kafr El Sheikh", L"Idfu", L"Shibin El Kom", L"Minya", L"Beheira", L"Daqahliya", L"North Sinai", L"Red Sea", L"Sharqiya"
			});
			this->comboBox5->Location = System::Drawing::Point(510, 125);
			this->comboBox5->Margin = System::Windows::Forms::Padding(2);
			this->comboBox5->Name = L"comboBox5";
			this->comboBox5->Size = System::Drawing::Size(158, 21);
			this->comboBox5->TabIndex = 51;
			// 
			// comboBox7
			// 
			this->comboBox7->BackColor = System::Drawing::Color::Azure;
			this->comboBox7->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox7->FormattingEnabled = true;
			this->comboBox7->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Level 1", L"Level 2", L"Level 3" });
			this->comboBox7->Location = System::Drawing::Point(98, 225);
			this->comboBox7->Margin = System::Windows::Forms::Padding(2);
			this->comboBox7->Name = L"comboBox7";
			this->comboBox7->Size = System::Drawing::Size(158, 21);
			this->comboBox7->TabIndex = 52;
			// 
			// comboBox6
			// 
			this->comboBox6->BackColor = System::Drawing::Color::Azure;
			this->comboBox6->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox6->FormattingEnabled = true;
			this->comboBox6->Items->AddRange(gcnew cli::array< System::Object^  >(34) {
				L"Cairo", L"Alexandria", L"Giza", L"Qalyubia",
					L"Port Said", L"Suez", L"Luxor", L"El Mansura", L"El Mahalla El Kubra", L"Tanta", L"Ismailia", L"Assiut", L"Fayoum", L"Zagazig",
					L"Aswan", L"Damietta", L"Damanhur", L"El Minya", L"Beni Suef", L"Qena", L"Sohag", L"Hurghada", L"Marsa Matruh", L"Arish", L"Banha",
					L"Kafr El Sheikh", L"Idfu", L"Shibin El Kom", L"Minya", L"Beheira", L"Daqahliya", L"North Sinai", L"Red Sea", L"Sharqiya"
			});
			this->comboBox6->Location = System::Drawing::Point(100, 125);
			this->comboBox6->Margin = System::Windows::Forms::Padding(2);
			this->comboBox6->Name = L"comboBox6";
			this->comboBox6->Size = System::Drawing::Size(158, 21);
			this->comboBox6->TabIndex = 52;
			// 
			// label63
			// 
			this->label63->AutoSize = true;
			this->label63->BackColor = System::Drawing::Color::LightSkyBlue;
			this->label63->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label63->Location = System::Drawing::Point(325, 331);
			this->label63->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label63->Name = L"label63";
			this->label63->Size = System::Drawing::Size(82, 20);
			this->label63->TabIndex = 47;
			this->label63->Text = L"Minutes :";
			// 
			// label62
			// 
			this->label62->AutoSize = true;
			this->label62->BackColor = System::Drawing::Color::LightSkyBlue;
			this->label62->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label62->Location = System::Drawing::Point(94, 331);
			this->label62->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label62->Name = L"label62";
			this->label62->Size = System::Drawing::Size(67, 20);
			this->label62->TabIndex = 48;
			this->label62->Text = L"Hours :";
			this->label62->Click += gcnew System::EventHandler(this, &MyForm::label62_Click);
			// 
			// label57
			// 
			this->label57->AutoSize = true;
			this->label57->BackColor = System::Drawing::Color::LightSkyBlue;
			this->label57->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label57->Location = System::Drawing::Point(436, 122);
			this->label57->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label57->Name = L"label57";
			this->label57->Size = System::Drawing::Size(39, 20);
			this->label57->TabIndex = 47;
			this->label57->Text = L"To :";
			// 
			// label58
			// 
			this->label58->AutoSize = true;
			this->label58->BackColor = System::Drawing::Color::LightSkyBlue;
			this->label58->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label58->Location = System::Drawing::Point(24, 124);
			this->label58->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label58->Name = L"label58";
			this->label58->Size = System::Drawing::Size(60, 20);
			this->label58->TabIndex = 48;
			this->label58->Text = L"From :";
			// 
			// label61
			// 
			this->label61->AutoSize = true;
			this->label61->BackColor = System::Drawing::Color::LightSkyBlue;
			this->label61->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label61->Location = System::Drawing::Point(41, 278);
			this->label61->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label61->Name = L"label61";
			this->label61->Size = System::Drawing::Size(78, 26);
			this->label61->TabIndex = 49;
			this->label61->Text = L"Time :";
			// 
			// label59
			// 
			this->label59->AutoSize = true;
			this->label59->BackColor = System::Drawing::Color::LightSkyBlue;
			this->label59->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label59->Location = System::Drawing::Point(37, 184);
			this->label59->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label59->Name = L"label59";
			this->label59->Size = System::Drawing::Size(128, 26);
			this->label59->TabIndex = 49;
			this->label59->Text = L"Car Level :";
			// 
			// label60
			// 
			this->label60->AutoSize = true;
			this->label60->BackColor = System::Drawing::Color::LightSkyBlue;
			this->label60->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label60->Location = System::Drawing::Point(37, 46);
			this->label60->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label60->Name = L"label60";
			this->label60->Size = System::Drawing::Size(102, 26);
			this->label60->TabIndex = 50;
			this->label60->Text = L"Location";
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->BackColor = System::Drawing::Color::LightSkyBlue;
			this->label40->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label40->Location = System::Drawing::Point(263, 0);
			this->label40->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(206, 29);
			this->label40->TabIndex = 0;
			this->label40->Text = L"Schedule a Ride";
			// 
			// pn_viewHistory
			// 
			this->pn_viewHistory->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pn_viewHistory.BackgroundImage")));
			this->pn_viewHistory->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pn_viewHistory->Controls->Add(this->total_rides);
			this->pn_viewHistory->Controls->Add(this->btn_clear_rider_history);
			this->pn_viewHistory->Controls->Add(this->fpn_rider_history);
			this->pn_viewHistory->Controls->Add(this->label38);
			this->pn_viewHistory->Location = System::Drawing::Point(0, 0);
			this->pn_viewHistory->Margin = System::Windows::Forms::Padding(2);
			this->pn_viewHistory->Name = L"pn_viewHistory";
			this->pn_viewHistory->Size = System::Drawing::Size(713, 437);
			this->pn_viewHistory->TabIndex = 0;
			// 
			// total_rides
			// 
			this->total_rides->AutoSize = true;
			this->total_rides->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(206)),
				static_cast<System::Int32>(static_cast<System::Byte>(212)));
			this->total_rides->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->total_rides->Location = System::Drawing::Point(51, 36);
			this->total_rides->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->total_rides->Name = L"total_rides";
			this->total_rides->Size = System::Drawing::Size(105, 17);
			this->total_rides->TabIndex = 3;
			this->total_rides->Text = L"Total rides: 0";
			// 
			// btn_clear_rider_history
			// 
			this->btn_clear_rider_history->AccessibleRole = System::Windows::Forms::AccessibleRole::Clock;
			this->btn_clear_rider_history->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(122)),
				static_cast<System::Int32>(static_cast<System::Byte>(206)), static_cast<System::Int32>(static_cast<System::Byte>(212)));
			this->btn_clear_rider_history->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btn_clear_rider_history->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(130)), static_cast<System::Int32>(static_cast<System::Byte>(130)));
			this->btn_clear_rider_history->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_clear_rider_history->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			this->btn_clear_rider_history->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_clear_rider_history.Image")));
			this->btn_clear_rider_history->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_clear_rider_history->Location = System::Drawing::Point(577, 19);
			this->btn_clear_rider_history->Name = L"btn_clear_rider_history";
			this->btn_clear_rider_history->Size = System::Drawing::Size(111, 36);
			this->btn_clear_rider_history->TabIndex = 2;
			this->btn_clear_rider_history->Text = L"Clear history";
			this->btn_clear_rider_history->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_clear_rider_history->UseVisualStyleBackColor = false;
			this->btn_clear_rider_history->Click += gcnew System::EventHandler(this, &MyForm::btn_clear_rider_history_Click);
			// 
			// fpn_rider_history
			// 
			this->fpn_rider_history->AutoScroll = true;
			this->fpn_rider_history->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(131)), static_cast<System::Int32>(static_cast<System::Byte>(136)));
			this->fpn_rider_history->Location = System::Drawing::Point(51, 60);
			this->fpn_rider_history->Name = L"fpn_rider_history";
			this->fpn_rider_history->Size = System::Drawing::Size(637, 364);
			this->fpn_rider_history->TabIndex = 1;
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(122)), static_cast<System::Int32>(static_cast<System::Byte>(206)),
				static_cast<System::Int32>(static_cast<System::Byte>(212)));
			this->label38->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label38->Location = System::Drawing::Point(288, 3);
			this->label38->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(158, 29);
			this->label38->TabIndex = 0;
			this->label38->Text = L"View History";
			// 
			// pictureBox19
			// 
			this->pictureBox19->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox19.Image")));
			this->pictureBox19->Location = System::Drawing::Point(0, 0);
			this->pictureBox19->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox19->Name = L"pictureBox19";
			this->pictureBox19->Size = System::Drawing::Size(712, 439);
			this->pictureBox19->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox19->TabIndex = 52;
			this->pictureBox19->TabStop = false;
			// 
			// pn_rate_captain
			// 
			this->pn_rate_captain->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->pn_rate_captain->Controls->Add(this->pictureBox30);
			this->pn_rate_captain->Controls->Add(this->rating_error);
			this->pn_rate_captain->Controls->Add(this->btn_ok);
			this->pn_rate_captain->Controls->Add(this->comboBox14);
			this->pn_rate_captain->Controls->Add(this->label96);
			this->pn_rate_captain->Controls->Add(this->label95);
			this->pn_rate_captain->Controls->Add(this->pictureBox31);
			this->pn_rate_captain->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_rate_captain->Location = System::Drawing::Point(0, 0);
			this->pn_rate_captain->Name = L"pn_rate_captain";
			this->pn_rate_captain->Size = System::Drawing::Size(712, 435);
			this->pn_rate_captain->TabIndex = 3;
			// 
			// pictureBox30
			// 
			this->pictureBox30->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(125)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(197)));
			this->pictureBox30->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox30.Image")));
			this->pictureBox30->Location = System::Drawing::Point(98, 12);
			this->pictureBox30->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox30->Name = L"pictureBox30";
			this->pictureBox30->Size = System::Drawing::Size(60, 55);
			this->pictureBox30->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox30->TabIndex = 2;
			this->pictureBox30->TabStop = false;
			// 
			// rating_error
			// 
			this->rating_error->AutoSize = true;
			this->rating_error->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(131)), static_cast<System::Int32>(static_cast<System::Byte>(72)),
				static_cast<System::Int32>(static_cast<System::Byte>(202)));
			this->rating_error->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->rating_error->ForeColor = System::Drawing::Color::Red;
			this->rating_error->Location = System::Drawing::Point(234, 306);
			this->rating_error->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->rating_error->Name = L"rating_error";
			this->rating_error->Size = System::Drawing::Size(39, 17);
			this->rating_error->TabIndex = 12;
			this->rating_error->Text = L"error";
			this->rating_error->Visible = false;
			// 
			// btn_ok
			// 
			this->btn_ok->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(82)), static_cast<System::Int32>(static_cast<System::Byte>(126)),
				static_cast<System::Int32>(static_cast<System::Byte>(207)));
			this->btn_ok->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btn_ok->FlatAppearance->BorderSize = 0;
			this->btn_ok->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_ok->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_ok->Location = System::Drawing::Point(234, 331);
			this->btn_ok->Margin = System::Windows::Forms::Padding(2);
			this->btn_ok->Name = L"btn_ok";
			this->btn_ok->Size = System::Drawing::Size(267, 42);
			this->btn_ok->TabIndex = 11;
			this->btn_ok->Text = L"Ok";
			this->btn_ok->UseVisualStyleBackColor = false;
			this->btn_ok->Click += gcnew System::EventHandler(this, &MyForm::btn_ok_Click);
			// 
			// comboBox14
			// 
			this->comboBox14->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->comboBox14->Cursor = System::Windows::Forms::Cursors::Hand;
			this->comboBox14->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox14->Font = (gcnew System::Drawing::Font(L"Dubai Medium", 9.749999F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox14->FormattingEnabled = true;
			this->comboBox14->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"1 Star", L"2 Stars", L"3 Stars", L"4 Stars",
					L"5 Stars"
			});
			this->comboBox14->Location = System::Drawing::Point(102, 139);
			this->comboBox14->Name = L"comboBox14";
			this->comboBox14->Size = System::Drawing::Size(267, 30);
			this->comboBox14->TabIndex = 6;
			// 
			// label96
			// 
			this->label96->AutoSize = true;
			this->label96->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(107)), static_cast<System::Int32>(static_cast<System::Byte>(59)),
				static_cast<System::Int32>(static_cast<System::Byte>(167)));
			this->label96->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label96->ForeColor = System::Drawing::SystemColors::InactiveCaption;
			this->label96->Location = System::Drawing::Point(104, 118);
			this->label96->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label96->Name = L"label96";
			this->label96->Size = System::Drawing::Size(92, 17);
			this->label96->TabIndex = 5;
			this->label96->Text = L"Rate captain:";
			// 
			// label95
			// 
			this->label95->AutoSize = true;
			this->label95->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(131)), static_cast<System::Int32>(static_cast<System::Byte>(72)),
				static_cast<System::Int32>(static_cast<System::Byte>(202)));
			this->label95->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 25));
			this->label95->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->label95->Location = System::Drawing::Point(162, 29);
			this->label95->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label95->Name = L"label95";
			this->label95->Size = System::Drawing::Size(243, 39);
			this->label95->TabIndex = 4;
			this->label95->Text = L"Captain Rating";
			// 
			// pictureBox31
			// 
			this->pictureBox31->Cursor = System::Windows::Forms::Cursors::Default;
			this->pictureBox31->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox31->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox31.Image")));
			this->pictureBox31->Location = System::Drawing::Point(0, 0);
			this->pictureBox31->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox31->Name = L"pictureBox31";
			this->pictureBox31->Size = System::Drawing::Size(712, 435);
			this->pictureBox31->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox31->TabIndex = 2;
			this->pictureBox31->TabStop = false;
			this->pictureBox31->Click += gcnew System::EventHandler(this, &MyForm::pictureBox27_Click);
			// 
			// pn_penddingList
			// 
			this->pn_penddingList->BackColor = System::Drawing::Color::LightSkyBlue;
			this->pn_penddingList->Controls->Add(this->fpn_pendingList);
			this->pn_penddingList->Controls->Add(this->pictureBox20);
			this->pn_penddingList->Controls->Add(this->label39);
			this->pn_penddingList->Location = System::Drawing::Point(0, 0);
			this->pn_penddingList->Margin = System::Windows::Forms::Padding(2);
			this->pn_penddingList->Name = L"pn_penddingList";
			this->pn_penddingList->Size = System::Drawing::Size(712, 439);
			this->pn_penddingList->TabIndex = 0;
			// 
			// fpn_pendingList
			// 
			this->fpn_pendingList->AutoScroll = true;
			this->fpn_pendingList->BackColor = System::Drawing::Color::DarkCyan;
			this->fpn_pendingList->Location = System::Drawing::Point(48, 65);
			this->fpn_pendingList->Name = L"fpn_pendingList";
			this->fpn_pendingList->Padding = System::Windows::Forms::Padding(2);
			this->fpn_pendingList->Size = System::Drawing::Size(564, 361);
			this->fpn_pendingList->TabIndex = 2;
			// 
			// pictureBox20
			// 
			this->pictureBox20->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox20.Image")));
			this->pictureBox20->Location = System::Drawing::Point(629, 359);
			this->pictureBox20->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox20->Name = L"pictureBox20";
			this->pictureBox20->Size = System::Drawing::Size(79, 76);
			this->pictureBox20->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox20->TabIndex = 1;
			this->pictureBox20->TabStop = false;
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label39->Location = System::Drawing::Point(44, 24);
			this->label39->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(173, 29);
			this->label39->TabIndex = 0;
			this->label39->Text = L"Pendding List";
			// 
			// pictureBox17
			// 
			this->pictureBox17->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox17.BackgroundImage")));
			this->pictureBox17->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox17->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox17.Image")));
			this->pictureBox17->Location = System::Drawing::Point(0, 0);
			this->pictureBox17->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox17->Name = L"pictureBox17";
			this->pictureBox17->Size = System::Drawing::Size(712, 439);
			this->pictureBox17->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox17->TabIndex = 0;
			this->pictureBox17->TabStop = false;
			// 
			// pn_rider_schedule_list
			// 
			this->pn_rider_schedule_list->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)),
				static_cast<System::Int32>(static_cast<System::Byte>(57)), static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->pn_rider_schedule_list->Controls->Add(this->label109);
			this->pn_rider_schedule_list->Controls->Add(this->fpn_rider_schedule_list);
			this->pn_rider_schedule_list->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_rider_schedule_list->Location = System::Drawing::Point(0, 0);
			this->pn_rider_schedule_list->Name = L"pn_rider_schedule_list";
			this->pn_rider_schedule_list->Size = System::Drawing::Size(712, 435);
			this->pn_rider_schedule_list->TabIndex = 54;
			// 
			// label109
			// 
			this->label109->AutoSize = true;
			this->label109->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label109->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->label109->ForeColor = System::Drawing::SystemColors::InactiveBorder;
			this->label109->Location = System::Drawing::Point(68, 37);
			this->label109->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label109->Name = L"label109";
			this->label109->Size = System::Drawing::Size(127, 20);
			this->label109->TabIndex = 3;
			this->label109->Text = L"Scheduled rides:";
			// 
			// fpn_rider_schedule_list
			// 
			this->fpn_rider_schedule_list->AutoScroll = true;
			this->fpn_rider_schedule_list->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(21)),
				static_cast<System::Int32>(static_cast<System::Byte>(76)), static_cast<System::Int32>(static_cast<System::Byte>(121)));
			this->fpn_rider_schedule_list->Location = System::Drawing::Point(70, 69);
			this->fpn_rider_schedule_list->Name = L"fpn_rider_schedule_list";
			this->fpn_rider_schedule_list->Size = System::Drawing::Size(577, 335);
			this->fpn_rider_schedule_list->TabIndex = 0;
			// 
			// pn_rider_profile
			// 
			this->pn_rider_profile->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->pn_rider_profile->Controls->Add(this->panel3);
			this->pn_rider_profile->Controls->Add(this->pictureBox32);
			this->pn_rider_profile->Controls->Add(this->label103);
			this->pn_rider_profile->Controls->Add(this->label105);
			this->pn_rider_profile->Controls->Add(this->label106);
			this->pn_rider_profile->Controls->Add(this->label107);
			this->pn_rider_profile->Controls->Add(this->label108);
			this->pn_rider_profile->Controls->Add(this->label114);
			this->pn_rider_profile->Controls->Add(this->label116);
			this->pn_rider_profile->Controls->Add(this->label117);
			this->pn_rider_profile->Controls->Add(this->label118);
			this->pn_rider_profile->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_rider_profile->Location = System::Drawing::Point(0, 0);
			this->pn_rider_profile->Name = L"pn_rider_profile";
			this->pn_rider_profile->Size = System::Drawing::Size(712, 435);
			this->pn_rider_profile->TabIndex = 2;
			this->pn_rider_profile->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_rider_profile_Paint);
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::Color::White;
			this->panel3->Location = System::Drawing::Point(64, 277);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(453, 3);
			this->panel3->TabIndex = 17;
			// 
			// pictureBox32
			// 
			this->pictureBox32->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->pictureBox32->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox32.Image")));
			this->pictureBox32->Location = System::Drawing::Point(63, 26);
			this->pictureBox32->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox32->Name = L"pictureBox32";
			this->pictureBox32->Size = System::Drawing::Size(47, 43);
			this->pictureBox32->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox32->TabIndex = 16;
			this->pictureBox32->TabStop = false;
			// 
			// label103
			// 
			this->label103->AutoSize = true;
			this->label103->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label103->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label103->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label103->Location = System::Drawing::Point(66, 244);
			this->label103->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label103->Name = L"label103";
			this->label103->Size = System::Drawing::Size(86, 17);
			this->label103->TabIndex = 15;
			this->label103->Text = L"Username:";
			// 
			// label105
			// 
			this->label105->AutoSize = true;
			this->label105->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label105->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label105->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label105->Location = System::Drawing::Point(66, 200);
			this->label105->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label105->Name = L"label105";
			this->label105->Size = System::Drawing::Size(28, 17);
			this->label105->TabIndex = 15;
			this->label105->Text = L"ID:";
			// 
			// label106
			// 
			this->label106->AutoSize = true;
			this->label106->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label106->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->label106->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label106->Location = System::Drawing::Point(112, 42);
			this->label106->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label106->Name = L"label106";
			this->label106->Size = System::Drawing::Size(94, 20);
			this->label106->TabIndex = 14;
			this->label106->Text = L"User Info :";
			// 
			// label107
			// 
			this->label107->AutoSize = true;
			this->label107->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label107->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label107->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label107->Location = System::Drawing::Point(64, 153);
			this->label107->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label107->Name = L"label107";
			this->label107->Size = System::Drawing::Size(113, 17);
			this->label107->TabIndex = 13;
			this->label107->Text = L"Second Name:";
			// 
			// label108
			// 
			this->label108->AutoSize = true;
			this->label108->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label108->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label108->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label108->Location = System::Drawing::Point(64, 110);
			this->label108->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label108->Name = L"label108";
			this->label108->Size = System::Drawing::Size(91, 17);
			this->label108->TabIndex = 12;
			this->label108->Text = L"First Name:";
			// 
			// label114
			// 
			this->label114->AutoSize = true;
			this->label114->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label114->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label114->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label114->Location = System::Drawing::Point(233, 246);
			this->label114->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label114->Name = L"label114";
			this->label114->Size = System::Drawing::Size(79, 17);
			this->label114->TabIndex = 2;
			this->label114->Text = L"username";
			// 
			// label116
			// 
			this->label116->AutoSize = true;
			this->label116->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label116->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label116->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label116->Location = System::Drawing::Point(233, 198);
			this->label116->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label116->Name = L"label116";
			this->label116->Size = System::Drawing::Size(21, 17);
			this->label116->TabIndex = 1;
			this->label116->Text = L"id";
			// 
			// label117
			// 
			this->label117->AutoSize = true;
			this->label117->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label117->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label117->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label117->Location = System::Drawing::Point(233, 153);
			this->label117->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label117->Name = L"label117";
			this->label117->Size = System::Drawing::Size(104, 17);
			this->label117->TabIndex = 2;
			this->label117->Text = L"second name";
			// 
			// label118
			// 
			this->label118->AutoSize = true;
			this->label118->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label118->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label118->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label118->Location = System::Drawing::Point(233, 113);
			this->label118->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label118->Name = L"label118";
			this->label118->Size = System::Drawing::Size(80, 17);
			this->label118->TabIndex = 1;
			this->label118->Text = L"first name";
			// 
			// fpn_rider_status
			// 
			this->fpn_rider_status->BackColor = System::Drawing::Color::LightSteelBlue;
			this->fpn_rider_status->Controls->Add(this->status_panel);
			this->fpn_rider_status->Controls->Add(this->pictureBox28);
			this->fpn_rider_status->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->fpn_rider_status->Location = System::Drawing::Point(0, 435);
			this->fpn_rider_status->Name = L"fpn_rider_status";
			this->fpn_rider_status->Padding = System::Windows::Forms::Padding(4);
			this->fpn_rider_status->Size = System::Drawing::Size(712, 59);
			this->fpn_rider_status->TabIndex = 53;
			// 
			// status_panel
			// 
			this->status_panel->BackColor = System::Drawing::Color::Linen;
			this->status_panel->Controls->Add(this->status_message);
			this->status_panel->Controls->Add(this->pictureBox29);
			this->status_panel->Controls->Add(this->pictureBox27);
			this->status_panel->Location = System::Drawing::Point(7, 7);
			this->status_panel->Name = L"status_panel";
			this->status_panel->Size = System::Drawing::Size(641, 45);
			this->status_panel->TabIndex = 18;
			this->status_panel->Visible = false;
			// 
			// status_message
			// 
			this->status_message->AutoSize = true;
			this->status_message->BackColor = System::Drawing::Color::Linen;
			this->status_message->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->status_message->Location = System::Drawing::Point(33, 18);
			this->status_message->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->status_message->Name = L"status_message";
			this->status_message->Size = System::Drawing::Size(121, 17);
			this->status_message->TabIndex = 2;
			this->status_message->Text = L"status message";
			// 
			// pictureBox29
			// 
			this->pictureBox29->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox29->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox29.Image")));
			this->pictureBox29->Location = System::Drawing::Point(2, -1);
			this->pictureBox29->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox29->Name = L"pictureBox29";
			this->pictureBox29->Size = System::Drawing::Size(26, 25);
			this->pictureBox29->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox29->TabIndex = 2;
			this->pictureBox29->TabStop = false;
			this->pictureBox29->Click += gcnew System::EventHandler(this, &MyForm::pictureBox27_Click);
			// 
			// pictureBox27
			// 
			this->pictureBox27->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox27->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox27.Image")));
			this->pictureBox27->Location = System::Drawing::Point(614, -1);
			this->pictureBox27->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox27->Name = L"pictureBox27";
			this->pictureBox27->Size = System::Drawing::Size(26, 25);
			this->pictureBox27->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox27->TabIndex = 2;
			this->pictureBox27->TabStop = false;
			this->pictureBox27->Click += gcnew System::EventHandler(this, &MyForm::pictureBox27_Click);
			// 
			// pictureBox28
			// 
			this->pictureBox28->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox28->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox28.Image")));
			this->pictureBox28->Location = System::Drawing::Point(653, 6);
			this->pictureBox28->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox28->Name = L"pictureBox28";
			this->pictureBox28->Size = System::Drawing::Size(49, 50);
			this->pictureBox28->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox28->TabIndex = 2;
			this->pictureBox28->TabStop = false;
			this->pictureBox28->Click += gcnew System::EventHandler(this, &MyForm::pictureBox28_Click);
			// 
			// pn_riderInfo
			// 
			this->pn_riderInfo->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pn_riderInfo.BackgroundImage")));
			this->pn_riderInfo->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pn_riderInfo->Controls->Add(this->btn_schedule_list);
			this->pn_riderInfo->Controls->Add(this->panel5);
			this->pn_riderInfo->Controls->Add(this->btn_rider_profile);
			this->pn_riderInfo->Controls->Add(this->button27);
			this->pn_riderInfo->Controls->Add(this->button26);
			this->pn_riderInfo->Controls->Add(this->button25);
			this->pn_riderInfo->Controls->Add(this->button24);
			this->pn_riderInfo->Controls->Add(this->button23);
			this->pn_riderInfo->Controls->Add(this->button22);
			this->pn_riderInfo->Controls->Add(this->pictureBox16);
			this->pn_riderInfo->Location = System::Drawing::Point(711, 0);
			this->pn_riderInfo->Margin = System::Windows::Forms::Padding(2);
			this->pn_riderInfo->Name = L"pn_riderInfo";
			this->pn_riderInfo->Size = System::Drawing::Size(217, 494);
			this->pn_riderInfo->TabIndex = 0;
			// 
			// btn_schedule_list
			// 
			this->btn_schedule_list->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(82)),
				static_cast<System::Int32>(static_cast<System::Byte>(126)), static_cast<System::Int32>(static_cast<System::Byte>(207)));
			this->btn_schedule_list->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btn_schedule_list->FlatAppearance->BorderSize = 0;
			this->btn_schedule_list->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_schedule_list->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_schedule_list->ForeColor = System::Drawing::SystemColors::Control;
			this->btn_schedule_list->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_schedule_list.Image")));
			this->btn_schedule_list->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_schedule_list->Location = System::Drawing::Point(-1, 218);
			this->btn_schedule_list->Margin = System::Windows::Forms::Padding(2);
			this->btn_schedule_list->Name = L"btn_schedule_list";
			this->btn_schedule_list->Size = System::Drawing::Size(218, 45);
			this->btn_schedule_list->TabIndex = 20;
			this->btn_schedule_list->Text = L"Schedule list";
			this->btn_schedule_list->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_schedule_list->UseVisualStyleBackColor = false;
			this->btn_schedule_list->Click += gcnew System::EventHandler(this, &MyForm::btn_schedule_list_Click);
			// 
			// panel5
			// 
			this->panel5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(37)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(190)));
			this->panel5->Controls->Add(this->rider_fullname);
			this->panel5->Controls->Add(this->rider_clock);
			this->panel5->Controls->Add(this->label55);
			this->panel5->Location = System::Drawing::Point(-1, 105);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(218, 65);
			this->panel5->TabIndex = 19;
			// 
			// rider_fullname
			// 
			this->rider_fullname->AutoSize = true;
			this->rider_fullname->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(37)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(190)));
			this->rider_fullname->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold));
			this->rider_fullname->ForeColor = System::Drawing::SystemColors::InactiveBorder;
			this->rider_fullname->Location = System::Drawing::Point(10, 8);
			this->rider_fullname->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->rider_fullname->Name = L"rider_fullname";
			this->rider_fullname->Size = System::Drawing::Size(73, 17);
			this->rider_fullname->TabIndex = 3;
			this->rider_fullname->Text = L"Fullname";
			// 
			// rider_clock
			// 
			this->rider_clock->AutoSize = true;
			this->rider_clock->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(37)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(190)));
			this->rider_clock->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rider_clock->ForeColor = System::Drawing::SystemColors::InactiveBorder;
			this->rider_clock->Location = System::Drawing::Point(69, 44);
			this->rider_clock->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->rider_clock->Name = L"rider_clock";
			this->rider_clock->Size = System::Drawing::Size(38, 17);
			this->rider_clock->TabIndex = 18;
			this->rider_clock->Text = L"time";
			// 
			// label55
			// 
			this->label55->AutoSize = true;
			this->label55->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(37)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(190)));
			this->label55->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label55->ForeColor = System::Drawing::SystemColors::InactiveBorder;
			this->label55->Location = System::Drawing::Point(7, 44);
			this->label55->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label55->Name = L"label55";
			this->label55->Size = System::Drawing::Size(48, 17);
			this->label55->TabIndex = 17;
			this->label55->Text = L"Time:";
			// 
			// btn_rider_profile
			// 
			this->btn_rider_profile->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(82)),
				static_cast<System::Int32>(static_cast<System::Byte>(126)), static_cast<System::Int32>(static_cast<System::Byte>(207)));
			this->btn_rider_profile->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btn_rider_profile->FlatAppearance->BorderSize = 0;
			this->btn_rider_profile->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_rider_profile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_rider_profile->ForeColor = System::Drawing::SystemColors::Control;
			this->btn_rider_profile->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_rider_profile.Image")));
			this->btn_rider_profile->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_rider_profile->Location = System::Drawing::Point(1, 397);
			this->btn_rider_profile->Margin = System::Windows::Forms::Padding(2);
			this->btn_rider_profile->Name = L"btn_rider_profile";
			this->btn_rider_profile->Size = System::Drawing::Size(218, 45);
			this->btn_rider_profile->TabIndex = 10;
			this->btn_rider_profile->Text = L"My profile";
			this->btn_rider_profile->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_rider_profile->UseVisualStyleBackColor = false;
			this->btn_rider_profile->Click += gcnew System::EventHandler(this, &MyForm::btn_rider_profile_Click);
			// 
			// button27
			// 
			this->button27->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(82)), static_cast<System::Int32>(static_cast<System::Byte>(126)),
				static_cast<System::Int32>(static_cast<System::Byte>(207)));
			this->button27->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button27->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button27->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Bold));
			this->button27->ForeColor = System::Drawing::SystemColors::Control;
			this->button27->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button27.Image")));
			this->button27->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button27->Location = System::Drawing::Point(1, 442);
			this->button27->Margin = System::Windows::Forms::Padding(2);
			this->button27->Name = L"button27";
			this->button27->Size = System::Drawing::Size(109, 50);
			this->button27->TabIndex = 9;
			this->button27->Text = L"Back";
			this->button27->UseVisualStyleBackColor = false;
			this->button27->Click += gcnew System::EventHandler(this, &MyForm::button27_Click);
			// 
			// button26
			// 
			this->button26->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(82)), static_cast<System::Int32>(static_cast<System::Byte>(126)),
				static_cast<System::Int32>(static_cast<System::Byte>(207)));
			this->button26->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button26->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button26->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Bold));
			this->button26->ForeColor = System::Drawing::SystemColors::Control;
			this->button26->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button26.Image")));
			this->button26->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button26->Location = System::Drawing::Point(112, 442);
			this->button26->Margin = System::Windows::Forms::Padding(2);
			this->button26->Name = L"button26";
			this->button26->Size = System::Drawing::Size(104, 50);
			this->button26->TabIndex = 8;
			this->button26->Text = L"Log Out";
			this->button26->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button26->UseVisualStyleBackColor = false;
			this->button26->Click += gcnew System::EventHandler(this, &MyForm::button26_Click);
			// 
			// button25
			// 
			this->button25->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(82)), static_cast<System::Int32>(static_cast<System::Byte>(126)),
				static_cast<System::Int32>(static_cast<System::Byte>(207)));
			this->button25->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button25->FlatAppearance->BorderSize = 0;
			this->button25->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button25->ForeColor = System::Drawing::SystemColors::Control;
			this->button25->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button25.Image")));
			this->button25->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button25->Location = System::Drawing::Point(1, 352);
			this->button25->Margin = System::Windows::Forms::Padding(2);
			this->button25->Name = L"button25";
			this->button25->Size = System::Drawing::Size(218, 45);
			this->button25->TabIndex = 7;
			this->button25->Text = L"View History";
			this->button25->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button25->UseVisualStyleBackColor = false;
			this->button25->Click += gcnew System::EventHandler(this, &MyForm::button25_Click);
			// 
			// button24
			// 
			this->button24->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(82)), static_cast<System::Int32>(static_cast<System::Byte>(126)),
				static_cast<System::Int32>(static_cast<System::Byte>(207)));
			this->button24->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button24->FlatAppearance->BorderSize = 0;
			this->button24->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button24->ForeColor = System::Drawing::SystemColors::Control;
			this->button24->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button24.Image")));
			this->button24->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button24->Location = System::Drawing::Point(0, 307);
			this->button24->Margin = System::Windows::Forms::Padding(2);
			this->button24->Name = L"button24";
			this->button24->Size = System::Drawing::Size(218, 45);
			this->button24->TabIndex = 6;
			this->button24->Text = L"Pendding List";
			this->button24->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button24->UseVisualStyleBackColor = false;
			this->button24->Click += gcnew System::EventHandler(this, &MyForm::button24_Click);
			// 
			// button23
			// 
			this->button23->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(82)), static_cast<System::Int32>(static_cast<System::Byte>(126)),
				static_cast<System::Int32>(static_cast<System::Byte>(207)));
			this->button23->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button23->FlatAppearance->BorderSize = 0;
			this->button23->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button23->ForeColor = System::Drawing::SystemColors::Control;
			this->button23->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button23.Image")));
			this->button23->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button23->Location = System::Drawing::Point(1, 262);
			this->button23->Margin = System::Windows::Forms::Padding(2);
			this->button23->Name = L"button23";
			this->button23->Size = System::Drawing::Size(218, 45);
			this->button23->TabIndex = 5;
			this->button23->Text = L"Schedule a Ride";
			this->button23->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button23->UseVisualStyleBackColor = false;
			this->button23->Click += gcnew System::EventHandler(this, &MyForm::button23_Click);
			// 
			// button22
			// 
			this->button22->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(82)), static_cast<System::Int32>(static_cast<System::Byte>(126)),
				static_cast<System::Int32>(static_cast<System::Byte>(207)));
			this->button22->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button22->FlatAppearance->BorderSize = 0;
			this->button22->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button22->ForeColor = System::Drawing::SystemColors::Control;
			this->button22->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button22.Image")));
			this->button22->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button22->Location = System::Drawing::Point(0, 173);
			this->button22->Margin = System::Windows::Forms::Padding(2);
			this->button22->Name = L"button22";
			this->button22->Size = System::Drawing::Size(218, 45);
			this->button22->TabIndex = 4;
			this->button22->Text = L"Request a Ride";
			this->button22->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button22->UseVisualStyleBackColor = false;
			this->button22->Click += gcnew System::EventHandler(this, &MyForm::button22_Click);
			// 
			// pictureBox16
			// 
			this->pictureBox16->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox16->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox16.Image")));
			this->pictureBox16->Location = System::Drawing::Point(64, 8);
			this->pictureBox16->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox16->Name = L"pictureBox16";
			this->pictureBox16->Size = System::Drawing::Size(94, 86);
			this->pictureBox16->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox16->TabIndex = 1;
			this->pictureBox16->TabStop = false;
			// 
			// pn_captainMenu
			// 
			this->pn_captainMenu->Controls->Add(this->pn_search_riders);
			this->pn_captainMenu->Controls->Add(this->pn_carInfo);
			this->pn_captainMenu->Controls->Add(this->pictureBox35);
			this->pn_captainMenu->Controls->Add(this->pictureBox13);
			this->pn_captainMenu->Controls->Add(this->pn_schedule_requests);
			this->pn_captainMenu->Controls->Add(this->pn_profile);
			this->pn_captainMenu->Controls->Add(this->pn_status);
			this->pn_captainMenu->Controls->Add(this->pn_menu_list);
			this->pn_captainMenu->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_captainMenu->Location = System::Drawing::Point(0, 34);
			this->pn_captainMenu->Margin = System::Windows::Forms::Padding(2);
			this->pn_captainMenu->Name = L"pn_captainMenu";
			this->pn_captainMenu->Size = System::Drawing::Size(928, 494);
			this->pn_captainMenu->TabIndex = 51;
			// 
			// pn_search_riders
			// 
			this->pn_search_riders->Controls->Add(this->button32);
			this->pn_search_riders->Controls->Add(this->search_anim);
			this->pn_search_riders->Controls->Add(this->fpn_riders_around);
			this->pn_search_riders->Controls->Add(this->label93);
			this->pn_search_riders->Controls->Add(this->pictureBox36);
			this->pn_search_riders->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_search_riders->Location = System::Drawing::Point(0, 0);
			this->pn_search_riders->Margin = System::Windows::Forms::Padding(2);
			this->pn_search_riders->Name = L"pn_search_riders";
			this->pn_search_riders->Size = System::Drawing::Size(712, 423);
			this->pn_search_riders->TabIndex = 57;
			// 
			// button32
			// 
			this->button32->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->button32->Location = System::Drawing::Point(206, 386);
			this->button32->Name = L"button32";
			this->button32->Size = System::Drawing::Size(104, 31);
			this->button32->TabIndex = 53;
			this->button32->Text = L"Refresh";
			this->button32->UseVisualStyleBackColor = true;
			this->button32->Click += gcnew System::EventHandler(this, &MyForm::button32_Click);
			// 
			// search_anim
			// 
			this->search_anim->Cursor = System::Windows::Forms::Cursors::Hand;
			this->search_anim->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"search_anim.Image")));
			this->search_anim->Location = System::Drawing::Point(648, 364);
			this->search_anim->Margin = System::Windows::Forms::Padding(2);
			this->search_anim->Name = L"search_anim";
			this->search_anim->Size = System::Drawing::Size(63, 59);
			this->search_anim->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->search_anim->TabIndex = 3;
			this->search_anim->TabStop = false;
			this->search_anim->Visible = false;
			// 
			// fpn_riders_around
			// 
			this->fpn_riders_around->AutoScroll = true;
			this->fpn_riders_around->Location = System::Drawing::Point(5, 42);
			this->fpn_riders_around->Name = L"fpn_riders_around";
			this->fpn_riders_around->Padding = System::Windows::Forms::Padding(5);
			this->fpn_riders_around->Size = System::Drawing::Size(306, 338);
			this->fpn_riders_around->TabIndex = 52;
			// 
			// label93
			// 
			this->label93->AutoSize = true;
			this->label93->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label93->Location = System::Drawing::Point(59, 11);
			this->label93->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label93->Name = L"label93";
			this->label93->Size = System::Drawing::Size(160, 20);
			this->label93->TabIndex = 50;
			this->label93->Text = L"Riders around you:";
			// 
			// pictureBox36
			// 
			this->pictureBox36->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox36.Image")));
			this->pictureBox36->Location = System::Drawing::Point(0, 0);
			this->pictureBox36->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox36->Name = L"pictureBox36";
			this->pictureBox36->Size = System::Drawing::Size(712, 437);
			this->pictureBox36->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox36->TabIndex = 48;
			this->pictureBox36->TabStop = false;
			// 
			// pn_carInfo
			// 
			this->pn_carInfo->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pn_carInfo.BackgroundImage")));
			this->pn_carInfo->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pn_carInfo->Controls->Add(this->label_error);
			this->pn_carInfo->Controls->Add(this->button31);
			this->pn_carInfo->Controls->Add(this->comboBox10);
			this->pn_carInfo->Controls->Add(this->label71);
			this->pn_carInfo->Controls->Add(this->label72);
			this->pn_carInfo->Controls->Add(this->label70);
			this->pn_carInfo->Controls->Add(this->label69);
			this->pn_carInfo->Controls->Add(this->comboBox8);
			this->pn_carInfo->Controls->Add(this->comboBox9);
			this->pn_carInfo->Controls->Add(this->textBox18);
			this->pn_carInfo->Controls->Add(this->label51);
			this->pn_carInfo->Controls->Add(this->label50);
			this->pn_carInfo->Controls->Add(this->label49);
			this->pn_carInfo->Controls->Add(this->label48);
			this->pn_carInfo->Controls->Add(this->label30);
			this->pn_carInfo->Controls->Add(this->label46);
			this->pn_carInfo->Controls->Add(this->label47);
			this->pn_carInfo->Controls->Add(this->label42);
			this->pn_carInfo->Controls->Add(this->label45);
			this->pn_carInfo->Controls->Add(this->label43);
			this->pn_carInfo->Controls->Add(this->label44);
			this->pn_carInfo->Location = System::Drawing::Point(0, 0);
			this->pn_carInfo->Margin = System::Windows::Forms::Padding(2);
			this->pn_carInfo->Name = L"pn_carInfo";
			this->pn_carInfo->Size = System::Drawing::Size(712, 425);
			this->pn_carInfo->TabIndex = 0;
			// 
			// label_error
			// 
			this->label_error->AutoSize = true;
			this->label_error->BackColor = System::Drawing::Color::Silver;
			this->label_error->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11));
			this->label_error->ForeColor = System::Drawing::Color::Red;
			this->label_error->Location = System::Drawing::Point(72, 343);
			this->label_error->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_error->Name = L"label_error";
			this->label_error->Size = System::Drawing::Size(42, 18);
			this->label_error->TabIndex = 55;
			this->label_error->Text = L"Error";
			this->label_error->Visible = false;
			// 
			// button31
			// 
			this->button31->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->button31->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button31->FlatAppearance->BorderSize = 2;
			this->button31->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LimeGreen;
			this->button31->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Silver;
			this->button31->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button31->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button31->Location = System::Drawing::Point(510, 374);
			this->button31->Margin = System::Windows::Forms::Padding(2);
			this->button31->Name = L"button31";
			this->button31->Size = System::Drawing::Size(195, 44);
			this->button31->TabIndex = 54;
			this->button31->Text = L"Save";
			this->button31->UseVisualStyleBackColor = false;
			this->button31->Click += gcnew System::EventHandler(this, &MyForm::button31_Click);
			// 
			// comboBox10
			// 
			this->comboBox10->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox10->FormattingEnabled = true;
			this->comboBox10->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Level 1", L"Level 2", L"Level 3" });
			this->comboBox10->Location = System::Drawing::Point(425, 309);
			this->comboBox10->Name = L"comboBox10";
			this->comboBox10->Size = System::Drawing::Size(260, 21);
			this->comboBox10->TabIndex = 53;
			// 
			// label71
			// 
			this->label71->AutoSize = true;
			this->label71->BackColor = System::Drawing::Color::Silver;
			this->label71->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Bold));
			this->label71->Location = System::Drawing::Point(392, 138);
			this->label71->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label71->Name = L"label71";
			this->label71->Size = System::Drawing::Size(64, 22);
			this->label71->TabIndex = 52;
			this->label71->Text = L"Level:";
			// 
			// label72
			// 
			this->label72->AutoSize = true;
			this->label72->BackColor = System::Drawing::Color::Silver;
			this->label72->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Bold));
			this->label72->Location = System::Drawing::Point(392, 87);
			this->label72->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label72->Name = L"label72";
			this->label72->Size = System::Drawing::Size(64, 22);
			this->label72->TabIndex = 51;
			this->label72->Text = L"Color:";
			// 
			// label70
			// 
			this->label70->AutoSize = true;
			this->label70->BackColor = System::Drawing::Color::Silver;
			this->label70->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Bold));
			this->label70->Location = System::Drawing::Point(16, 142);
			this->label70->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label70->Name = L"label70";
			this->label70->Size = System::Drawing::Size(123, 22);
			this->label70->TabIndex = 50;
			this->label70->Text = L"Car Number:";
			// 
			// label69
			// 
			this->label69->AutoSize = true;
			this->label69->BackColor = System::Drawing::Color::Silver;
			this->label69->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Bold));
			this->label69->Location = System::Drawing::Point(16, 91);
			this->label69->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label69->Name = L"label69";
			this->label69->Size = System::Drawing::Size(61, 22);
			this->label69->TabIndex = 49;
			this->label69->Text = L"Type:";
			// 
			// comboBox8
			// 
			this->comboBox8->BackColor = System::Drawing::Color::WhiteSmoke;
			this->comboBox8->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox8->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->comboBox8->FormattingEnabled = true;
			this->comboBox8->Items->AddRange(gcnew cli::array< System::Object^  >(16) {
				L"Black", L"White", L"Blue", L"Yellow", L"Red",
					L"Green", L"Orange", L"Brown", L"Olive", L"Grey", L"Purple", L"Silver", L"Pink", L"Cyan", L"Rust", L"Sky"
			});
			this->comboBox8->Location = System::Drawing::Point(102, 307);
			this->comboBox8->Margin = System::Windows::Forms::Padding(2);
			this->comboBox8->Name = L"comboBox8";
			this->comboBox8->Size = System::Drawing::Size(202, 21);
			this->comboBox8->TabIndex = 47;
			// 
			// comboBox9
			// 
			this->comboBox9->BackColor = System::Drawing::Color::WhiteSmoke;
			this->comboBox9->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox9->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->comboBox9->FormattingEnabled = true;
			this->comboBox9->Items->AddRange(gcnew cli::array< System::Object^  >(14) {
				L"KIA", L"Audi", L"BMW", L"MITSUBISHI", L"HYUNDAI",
					L"NISSAN", L"CHERY", L"Mercedes", L"Skoda", L"FIAT", L"HONDA", L"TOYOTA", L"CHEVROLET", L"LADA"
			});
			this->comboBox9->Location = System::Drawing::Point(102, 243);
			this->comboBox9->Margin = System::Windows::Forms::Padding(2);
			this->comboBox9->Name = L"comboBox9";
			this->comboBox9->Size = System::Drawing::Size(202, 21);
			this->comboBox9->TabIndex = 46;
			// 
			// textBox18
			// 
			this->textBox18->BackColor = System::Drawing::Color::Silver;
			this->textBox18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox18->Location = System::Drawing::Point(501, 240);
			this->textBox18->Margin = System::Windows::Forms::Padding(2);
			this->textBox18->Multiline = true;
			this->textBox18->Name = L"textBox18";
			this->textBox18->Size = System::Drawing::Size(184, 24);
			this->textBox18->TabIndex = 17;
			// 
			// label51
			// 
			this->label51->AutoSize = true;
			this->label51->BackColor = System::Drawing::Color::Silver;
			this->label51->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->label51->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Bold));
			this->label51->Location = System::Drawing::Point(339, 307);
			this->label51->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(64, 22);
			this->label51->TabIndex = 15;
			this->label51->Text = L"Level:";
			// 
			// label50
			// 
			this->label50->AutoSize = true;
			this->label50->BackColor = System::Drawing::Color::Silver;
			this->label50->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->label50->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Bold));
			this->label50->Location = System::Drawing::Point(339, 241);
			this->label50->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label50->Name = L"label50";
			this->label50->Size = System::Drawing::Size(123, 22);
			this->label50->TabIndex = 14;
			this->label50->Text = L"Car Number:";
			// 
			// label49
			// 
			this->label49->AutoSize = true;
			this->label49->BackColor = System::Drawing::Color::Silver;
			this->label49->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->label49->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Bold));
			this->label49->Location = System::Drawing::Point(14, 241);
			this->label49->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label49->Name = L"label49";
			this->label49->Size = System::Drawing::Size(61, 22);
			this->label49->TabIndex = 13;
			this->label49->Text = L"Type:";
			// 
			// label48
			// 
			this->label48->AutoSize = true;
			this->label48->BackColor = System::Drawing::Color::Silver;
			this->label48->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->label48->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Bold));
			this->label48->Location = System::Drawing::Point(14, 306);
			this->label48->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label48->Name = L"label48";
			this->label48->Size = System::Drawing::Size(64, 22);
			this->label48->TabIndex = 12;
			this->label48->Text = L"Color:";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->BackColor = System::Drawing::Color::Gray;
			this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label30->Location = System::Drawing::Point(277, 0);
			this->label30->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(178, 31);
			this->label30->TabIndex = 0;
			this->label30->Text = L"Edit Car Info";
			// 
			// label46
			// 
			this->label46->AutoSize = true;
			this->label46->BackColor = System::Drawing::Color::Silver;
			this->label46->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Bold));
			this->label46->Location = System::Drawing::Point(574, 136);
			this->label46->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(58, 22);
			this->label46->TabIndex = 11;
			this->label46->Text = L"Level";
			// 
			// label47
			// 
			this->label47->AutoSize = true;
			this->label47->BackColor = System::Drawing::Color::Silver;
			this->label47->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label47->Location = System::Drawing::Point(14, 200);
			this->label47->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label47->Name = L"label47";
			this->label47->Size = System::Drawing::Size(197, 31);
			this->label47->TabIndex = 7;
			this->label47->Text = L"new Car Info :";
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->BackColor = System::Drawing::Color::Silver;
			this->label42->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label42->Location = System::Drawing::Point(15, 47);
			this->label42->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(331, 31);
			this->label42->TabIndex = 7;
			this->label42->Text = L"Current car information :";
			// 
			// label45
			// 
			this->label45->AutoSize = true;
			this->label45->BackColor = System::Drawing::Color::Silver;
			this->label45->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Bold));
			this->label45->Location = System::Drawing::Point(249, 142);
			this->label45->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(56, 22);
			this->label45->TabIndex = 10;
			this->label45->Text = L"Plate";
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->BackColor = System::Drawing::Color::Silver;
			this->label43->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Bold));
			this->label43->Location = System::Drawing::Point(248, 87);
			this->label43->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(55, 22);
			this->label43->TabIndex = 8;
			this->label43->Text = L"Type";
			// 
			// label44
			// 
			this->label44->AutoSize = true;
			this->label44->BackColor = System::Drawing::Color::Silver;
			this->label44->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Bold));
			this->label44->Location = System::Drawing::Point(574, 88);
			this->label44->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label44->Name = L"label44";
			this->label44->Size = System::Drawing::Size(58, 22);
			this->label44->TabIndex = 9;
			this->label44->Text = L"Color";
			this->label44->Click += gcnew System::EventHandler(this, &MyForm::label44_Click);
			// 
			// pictureBox35
			// 
			this->pictureBox35->BackColor = System::Drawing::Color::Navy;
			this->pictureBox35->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox35->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox35.Image")));
			this->pictureBox35->Location = System::Drawing::Point(0, 0);
			this->pictureBox35->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox35->Name = L"pictureBox35";
			this->pictureBox35->Size = System::Drawing::Size(712, 423);
			this->pictureBox35->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox35->TabIndex = 58;
			this->pictureBox35->TabStop = false;
			// 
			// pictureBox13
			// 
			this->pictureBox13->BackColor = System::Drawing::Color::Navy;
			this->pictureBox13->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox13->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox13.Image")));
			this->pictureBox13->Location = System::Drawing::Point(0, 0);
			this->pictureBox13->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox13->Name = L"pictureBox13";
			this->pictureBox13->Size = System::Drawing::Size(712, 423);
			this->pictureBox13->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox13->TabIndex = 2;
			this->pictureBox13->TabStop = false;
			// 
			// pn_schedule_requests
			// 
			this->pn_schedule_requests->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(24)),
				static_cast<System::Int32>(static_cast<System::Byte>(116)), static_cast<System::Int32>(static_cast<System::Byte>(165)));
			this->pn_schedule_requests->Controls->Add(this->fpn_schedule_requests);
			this->pn_schedule_requests->Controls->Add(this->label28);
			this->pn_schedule_requests->Location = System::Drawing::Point(0, 0);
			this->pn_schedule_requests->Margin = System::Windows::Forms::Padding(2);
			this->pn_schedule_requests->Name = L"pn_schedule_requests";
			this->pn_schedule_requests->Size = System::Drawing::Size(712, 425);
			this->pn_schedule_requests->TabIndex = 0;
			// 
			// fpn_schedule_requests
			// 
			this->fpn_schedule_requests->AutoScroll = true;
			this->fpn_schedule_requests->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(68)),
				static_cast<System::Int32>(static_cast<System::Byte>(188)), static_cast<System::Int32>(static_cast<System::Byte>(216)));
			this->fpn_schedule_requests->Location = System::Drawing::Point(28, 46);
			this->fpn_schedule_requests->Name = L"fpn_schedule_requests";
			this->fpn_schedule_requests->Size = System::Drawing::Size(640, 363);
			this->fpn_schedule_requests->TabIndex = 1;
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label28->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label28->Location = System::Drawing::Point(213, 7);
			this->label28->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(272, 31);
			this->label28->TabIndex = 0;
			this->label28->Text = L"Scheduled requests";
			// 
			// pn_profile
			// 
			this->pn_profile->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->pn_profile->Controls->Add(this->panel7);
			this->pn_profile->Controls->Add(this->pictureBox26);
			this->pn_profile->Controls->Add(this->pictureBox12);
			this->pn_profile->Controls->Add(this->label76);
			this->pn_profile->Controls->Add(this->label75);
			this->pn_profile->Controls->Add(this->label74);
			this->pn_profile->Controls->Add(this->label68);
			this->pn_profile->Controls->Add(this->label67);
			this->pn_profile->Controls->Add(this->label66);
			this->pn_profile->Controls->Add(this->label31);
			this->pn_profile->Controls->Add(this->label32);
			this->pn_profile->Controls->Add(this->label35);
			this->pn_profile->Controls->Add(this->label33);
			this->pn_profile->Controls->Add(this->label34);
			this->pn_profile->Controls->Add(this->label79);
			this->pn_profile->Controls->Add(this->label78);
			this->pn_profile->Controls->Add(this->label77);
			this->pn_profile->Controls->Add(this->label27);
			this->pn_profile->Controls->Add(this->label26);
			this->pn_profile->Location = System::Drawing::Point(0, 0);
			this->pn_profile->Name = L"pn_profile";
			this->pn_profile->Size = System::Drawing::Size(713, 425);
			this->pn_profile->TabIndex = 0;
			this->pn_profile->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_profile_Paint);
			// 
			// panel7
			// 
			this->panel7->BackColor = System::Drawing::Color::White;
			this->panel7->Location = System::Drawing::Point(21, 302);
			this->panel7->Name = L"panel7";
			this->panel7->Size = System::Drawing::Size(453, 3);
			this->panel7->TabIndex = 18;
			// 
			// pictureBox26
			// 
			this->pictureBox26->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->pictureBox26->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox26.Image")));
			this->pictureBox26->Location = System::Drawing::Point(344, 19);
			this->pictureBox26->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox26->Name = L"pictureBox26";
			this->pictureBox26->Size = System::Drawing::Size(47, 43);
			this->pictureBox26->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox26->TabIndex = 17;
			this->pictureBox26->TabStop = false;
			// 
			// pictureBox12
			// 
			this->pictureBox12->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->pictureBox12->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox12.Image")));
			this->pictureBox12->Location = System::Drawing::Point(20, 20);
			this->pictureBox12->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox12->Name = L"pictureBox12";
			this->pictureBox12->Size = System::Drawing::Size(47, 43);
			this->pictureBox12->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox12->TabIndex = 16;
			this->pictureBox12->TabStop = false;
			// 
			// label76
			// 
			this->label76->AutoSize = true;
			this->label76->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label76->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label76->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label76->Location = System::Drawing::Point(21, 255);
			this->label76->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label76->Name = L"label76";
			this->label76->Size = System::Drawing::Size(86, 17);
			this->label76->TabIndex = 15;
			this->label76->Text = L"Username:";
			// 
			// label75
			// 
			this->label75->AutoSize = true;
			this->label75->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label75->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label75->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label75->Location = System::Drawing::Point(21, 209);
			this->label75->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label75->Name = L"label75";
			this->label75->Size = System::Drawing::Size(105, 17);
			this->label75->TabIndex = 15;
			this->label75->Text = L"Location city:";
			// 
			// label74
			// 
			this->label74->AutoSize = true;
			this->label74->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label74->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label74->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label74->Location = System::Drawing::Point(21, 163);
			this->label74->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label74->Name = L"label74";
			this->label74->Size = System::Drawing::Size(28, 17);
			this->label74->TabIndex = 15;
			this->label74->Text = L"ID:";
			// 
			// label68
			// 
			this->label68->AutoSize = true;
			this->label68->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label68->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->label68->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label68->Location = System::Drawing::Point(69, 36);
			this->label68->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label68->Name = L"label68";
			this->label68->Size = System::Drawing::Size(94, 20);
			this->label68->TabIndex = 14;
			this->label68->Text = L"User Info :";
			// 
			// label67
			// 
			this->label67->AutoSize = true;
			this->label67->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label67->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label67->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label67->Location = System::Drawing::Point(19, 122);
			this->label67->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label67->Name = L"label67";
			this->label67->Size = System::Drawing::Size(113, 17);
			this->label67->TabIndex = 13;
			this->label67->Text = L"Second Name:";
			// 
			// label66
			// 
			this->label66->AutoSize = true;
			this->label66->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label66->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label66->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label66->Location = System::Drawing::Point(21, 79);
			this->label66->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label66->Name = L"label66";
			this->label66->Size = System::Drawing::Size(91, 17);
			this->label66->TabIndex = 12;
			this->label66->Text = L"First Name:";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->label31->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label31->Location = System::Drawing::Point(393, 31);
			this->label31->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(84, 20);
			this->label31->TabIndex = 7;
			this->label31->Text = L"Car Info :";
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label32->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label32->Location = System::Drawing::Point(386, 78);
			this->label32->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(39, 17);
			this->label32->TabIndex = 8;
			this->label32->Text = L"type";
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label35->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label35->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label35->Location = System::Drawing::Point(590, 123);
			this->label35->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(42, 17);
			this->label35->TabIndex = 11;
			this->label35->Text = L"level";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label33->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label33->Location = System::Drawing::Point(590, 75);
			this->label33->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(44, 17);
			this->label33->TabIndex = 9;
			this->label33->Text = L"color";
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label34->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label34->Location = System::Drawing::Point(387, 126);
			this->label34->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(35, 17);
			this->label34->TabIndex = 10;
			this->label34->Text = L"plat";
			// 
			// label79
			// 
			this->label79->AutoSize = true;
			this->label79->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label79->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label79->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label79->Location = System::Drawing::Point(188, 257);
			this->label79->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label79->Name = L"label79";
			this->label79->Size = System::Drawing::Size(79, 17);
			this->label79->TabIndex = 2;
			this->label79->Text = L"username";
			this->label79->Click += gcnew System::EventHandler(this, &MyForm::label27_Click);
			// 
			// label78
			// 
			this->label78->AutoSize = true;
			this->label78->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label78->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label78->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label78->Location = System::Drawing::Point(188, 209);
			this->label78->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label78->Name = L"label78";
			this->label78->Size = System::Drawing::Size(65, 17);
			this->label78->TabIndex = 2;
			this->label78->Text = L"location";
			this->label78->Click += gcnew System::EventHandler(this, &MyForm::label27_Click);
			// 
			// label77
			// 
			this->label77->AutoSize = true;
			this->label77->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label77->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label77->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label77->Location = System::Drawing::Point(188, 166);
			this->label77->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label77->Name = L"label77";
			this->label77->Size = System::Drawing::Size(21, 17);
			this->label77->TabIndex = 1;
			this->label77->Text = L"id";
			this->label77->Click += gcnew System::EventHandler(this, &MyForm::label26_Click);
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label27->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label27->Location = System::Drawing::Point(188, 122);
			this->label27->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(104, 17);
			this->label27->TabIndex = 2;
			this->label27->Text = L"second name";
			this->label27->Click += gcnew System::EventHandler(this, &MyForm::label27_Click);
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label26->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label26->Location = System::Drawing::Point(188, 82);
			this->label26->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(80, 17);
			this->label26->TabIndex = 1;
			this->label26->Text = L"first name";
			this->label26->Click += gcnew System::EventHandler(this, &MyForm::label26_Click);
			// 
			// pn_status
			// 
			this->pn_status->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->pn_status->Controls->Add(this->flowLayoutPanel16);
			this->pn_status->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->pn_status->Location = System::Drawing::Point(0, 423);
			this->pn_status->Name = L"pn_status";
			this->pn_status->Size = System::Drawing::Size(712, 71);
			this->pn_status->TabIndex = 56;
			// 
			// flowLayoutPanel16
			// 
			this->flowLayoutPanel16->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(131)), static_cast<System::Int32>(static_cast<System::Byte>(136)));
			this->flowLayoutPanel16->Controls->Add(this->rider_status_panel);
			this->flowLayoutPanel16->Controls->Add(this->pictureBox34);
			this->flowLayoutPanel16->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->flowLayoutPanel16->Location = System::Drawing::Point(0, 12);
			this->flowLayoutPanel16->Name = L"flowLayoutPanel16";
			this->flowLayoutPanel16->Padding = System::Windows::Forms::Padding(4);
			this->flowLayoutPanel16->Size = System::Drawing::Size(712, 59);
			this->flowLayoutPanel16->TabIndex = 54;
			// 
			// rider_status_panel
			// 
			this->rider_status_panel->BackColor = System::Drawing::Color::Linen;
			this->rider_status_panel->Controls->Add(this->label37);
			this->rider_status_panel->Controls->Add(this->pictureBox15);
			this->rider_status_panel->Controls->Add(this->pictureBox33);
			this->rider_status_panel->Location = System::Drawing::Point(7, 7);
			this->rider_status_panel->Name = L"rider_status_panel";
			this->rider_status_panel->Size = System::Drawing::Size(641, 45);
			this->rider_status_panel->TabIndex = 18;
			this->rider_status_panel->Visible = false;
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->BackColor = System::Drawing::Color::Linen;
			this->label37->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label37->Location = System::Drawing::Point(41, 12);
			this->label37->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(121, 17);
			this->label37->TabIndex = 2;
			this->label37->Text = L"status message";
			// 
			// pictureBox15
			// 
			this->pictureBox15->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox15->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox15.Image")));
			this->pictureBox15->Location = System::Drawing::Point(2, -1);
			this->pictureBox15->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox15->Name = L"pictureBox15";
			this->pictureBox15->Size = System::Drawing::Size(26, 25);
			this->pictureBox15->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox15->TabIndex = 2;
			this->pictureBox15->TabStop = false;
			// 
			// pictureBox33
			// 
			this->pictureBox33->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox33->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox33.Image")));
			this->pictureBox33->Location = System::Drawing::Point(614, -1);
			this->pictureBox33->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox33->Name = L"pictureBox33";
			this->pictureBox33->Size = System::Drawing::Size(26, 25);
			this->pictureBox33->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox33->TabIndex = 2;
			this->pictureBox33->TabStop = false;
			this->pictureBox33->Click += gcnew System::EventHandler(this, &MyForm::pictureBox33_Click);
			// 
			// pictureBox34
			// 
			this->pictureBox34->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox34->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox34.Image")));
			this->pictureBox34->Location = System::Drawing::Point(653, 6);
			this->pictureBox34->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox34->Name = L"pictureBox34";
			this->pictureBox34->Size = System::Drawing::Size(49, 50);
			this->pictureBox34->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox34->TabIndex = 2;
			this->pictureBox34->TabStop = false;
			this->pictureBox34->Click += gcnew System::EventHandler(this, &MyForm::pictureBox34_Click);
			// 
			// pn_menu_list
			// 
			this->pn_menu_list->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pn_menu_list.BackgroundImage")));
			this->pn_menu_list->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pn_menu_list->Controls->Add(this->btn_search);
			this->pn_menu_list->Controls->Add(this->panel6);
			this->pn_menu_list->Controls->Add(this->button30);
			this->pn_menu_list->Controls->Add(this->button19);
			this->pn_menu_list->Controls->Add(this->button18);
			this->pn_menu_list->Controls->Add(this->button17);
			this->pn_menu_list->Controls->Add(this->button16);
			this->pn_menu_list->Controls->Add(this->pictureBox14);
			this->pn_menu_list->Dock = System::Windows::Forms::DockStyle::Right;
			this->pn_menu_list->Location = System::Drawing::Point(712, 0);
			this->pn_menu_list->Margin = System::Windows::Forms::Padding(2);
			this->pn_menu_list->Name = L"pn_menu_list";
			this->pn_menu_list->Size = System::Drawing::Size(216, 494);
			this->pn_menu_list->TabIndex = 0;
			// 
			// btn_search
			// 
			this->btn_search->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(76)),
				static_cast<System::Int32>(static_cast<System::Byte>(121)));
			this->btn_search->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btn_search->FlatAppearance->BorderSize = 0;
			this->btn_search->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(131)), static_cast<System::Int32>(static_cast<System::Byte>(136)));
			this->btn_search->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_search->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->btn_search->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->btn_search->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_search.Image")));
			this->btn_search->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_search->Location = System::Drawing::Point(-1, 210);
			this->btn_search->Margin = System::Windows::Forms::Padding(2);
			this->btn_search->Name = L"btn_search";
			this->btn_search->Size = System::Drawing::Size(218, 60);
			this->btn_search->TabIndex = 18;
			this->btn_search->Text = L"Search a ride";
			this->btn_search->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_search->UseVisualStyleBackColor = false;
			this->btn_search->Click += gcnew System::EventHandler(this, &MyForm::btn_search_Click);
			// 
			// panel6
			// 
			this->panel6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(129)),
				static_cast<System::Int32>(static_cast<System::Byte>(176)));
			this->panel6->Controls->Add(this->label65);
			this->panel6->Controls->Add(this->captain_clock);
			this->panel6->Controls->Add(this->label29);
			this->panel6->Controls->Add(this->label80);
			this->panel6->Location = System::Drawing::Point(1, 109);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(215, 101);
			this->panel6->TabIndex = 17;
			// 
			// label65
			// 
			this->label65->AutoSize = true;
			this->label65->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(129)),
				static_cast<System::Int32>(static_cast<System::Byte>(176)));
			this->label65->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold));
			this->label65->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label65->Location = System::Drawing::Point(9, 11);
			this->label65->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label65->Name = L"label65";
			this->label65->Size = System::Drawing::Size(78, 17);
			this->label65->TabIndex = 13;
			this->label65->Text = L"full_name";
			// 
			// captain_clock
			// 
			this->captain_clock->AutoSize = true;
			this->captain_clock->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(129)),
				static_cast<System::Int32>(static_cast<System::Byte>(176)));
			this->captain_clock->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold));
			this->captain_clock->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->captain_clock->Location = System::Drawing::Point(66, 65);
			this->captain_clock->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->captain_clock->Name = L"captain_clock";
			this->captain_clock->Size = System::Drawing::Size(38, 17);
			this->captain_clock->TabIndex = 16;
			this->captain_clock->Text = L"time";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(129)),
				static_cast<System::Int32>(static_cast<System::Byte>(176)));
			this->label29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Bold));
			this->label29->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label29->Location = System::Drawing::Point(8, 35);
			this->label29->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(52, 22);
			this->label29->TabIndex = 12;
			this->label29->Text = L"Rate";
			// 
			// label80
			// 
			this->label80->AutoSize = true;
			this->label80->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(129)),
				static_cast<System::Int32>(static_cast<System::Byte>(176)));
			this->label80->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold));
			this->label80->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label80->Location = System::Drawing::Point(7, 65);
			this->label80->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label80->Name = L"label80";
			this->label80->Size = System::Drawing::Size(43, 17);
			this->label80->TabIndex = 15;
			this->label80->Text = L"Time";
			// 
			// button30
			// 
			this->button30->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(76)),
				static_cast<System::Int32>(static_cast<System::Byte>(121)));
			this->button30->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button30->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button30->FlatAppearance->BorderSize = 0;
			this->button30->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(131)), static_cast<System::Int32>(static_cast<System::Byte>(136)));
			this->button30->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->button30->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->button30->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button30.Image")));
			this->button30->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button30->Location = System::Drawing::Point(0, 390);
			this->button30->Margin = System::Windows::Forms::Padding(2);
			this->button30->Name = L"button30";
			this->button30->Size = System::Drawing::Size(218, 60);
			this->button30->TabIndex = 14;
			this->button30->Text = L"My Profile";
			this->button30->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button30->UseVisualStyleBackColor = false;
			this->button30->Click += gcnew System::EventHandler(this, &MyForm::button30_Click);
			// 
			// button19
			// 
			this->button19->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->button19->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button19->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button19->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button19->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button19->Location = System::Drawing::Point(0, 450);
			this->button19->Margin = System::Windows::Forms::Padding(2);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(113, 44);
			this->button19->TabIndex = 6;
			this->button19->Text = L"Back";
			this->button19->UseVisualStyleBackColor = false;
			this->button19->Click += gcnew System::EventHandler(this, &MyForm::button19_Click);
			// 
			// button18
			// 
			this->button18->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(76)),
				static_cast<System::Int32>(static_cast<System::Byte>(121)));
			this->button18->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button18->FlatAppearance->BorderSize = 0;
			this->button18->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(131)), static_cast<System::Int32>(static_cast<System::Byte>(136)));
			this->button18->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->button18->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->button18->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button18.Image")));
			this->button18->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button18->Location = System::Drawing::Point(-1, 330);
			this->button18->Margin = System::Windows::Forms::Padding(2);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(218, 60);
			this->button18->TabIndex = 5;
			this->button18->Text = L"Edit car info";
			this->button18->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button18->UseVisualStyleBackColor = false;
			this->button18->Click += gcnew System::EventHandler(this, &MyForm::button18_Click);
			// 
			// button17
			// 
			this->button17->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(76)),
				static_cast<System::Int32>(static_cast<System::Byte>(121)));
			this->button17->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button17->FlatAppearance->BorderSize = 0;
			this->button17->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(131)), static_cast<System::Int32>(static_cast<System::Byte>(136)));
			this->button17->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->button17->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->button17->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button17.Image")));
			this->button17->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button17->Location = System::Drawing::Point(-2, 270);
			this->button17->Margin = System::Windows::Forms::Padding(2);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(218, 60);
			this->button17->TabIndex = 5;
			this->button17->Text = L"Scheduled requests";
			this->button17->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button17->UseVisualStyleBackColor = false;
			this->button17->Click += gcnew System::EventHandler(this, &MyForm::button17_Click);
			// 
			// button16
			// 
			this->button16->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(112)));
			this->button16->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button16->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Red;
			this->button16->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button16->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button16->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button16->Location = System::Drawing::Point(117, 450);
			this->button16->Margin = System::Windows::Forms::Padding(2);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(99, 44);
			this->button16->TabIndex = 4;
			this->button16->Text = L"Log Out";
			this->button16->UseVisualStyleBackColor = false;
			this->button16->Click += gcnew System::EventHandler(this, &MyForm::button16_Click);
			// 
			// pictureBox14
			// 
			this->pictureBox14->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox14->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox14.Image")));
			this->pictureBox14->Location = System::Drawing::Point(62, 9);
			this->pictureBox14->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox14->Name = L"pictureBox14";
			this->pictureBox14->Size = System::Drawing::Size(94, 89);
			this->pictureBox14->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox14->TabIndex = 0;
			this->pictureBox14->TabStop = false;
			// 
			// pn_login_screan
			// 
			this->pn_login_screan->Controls->Add(this->pn_login);
			this->pn_login_screan->Controls->Add(this->pn_back);
			this->pn_login_screan->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_login_screan->Location = System::Drawing::Point(0, 34);
			this->pn_login_screan->Margin = System::Windows::Forms::Padding(2);
			this->pn_login_screan->Name = L"pn_login_screan";
			this->pn_login_screan->Size = System::Drawing::Size(928, 494);
			this->pn_login_screan->TabIndex = 2;
			// 
			// pn_login
			// 
			this->pn_login->Controls->Add(this->pictureBox25);
			this->pn_login->Controls->Add(this->pictureBox24);
			this->pn_login->Controls->Add(this->pictureBox23);
			this->pn_login->Controls->Add(this->pictureBox5);
			this->pn_login->Controls->Add(this->label64);
			this->pn_login->Controls->Add(this->label7);
			this->pn_login->Controls->Add(this->button7);
			this->pn_login->Controls->Add(this->button6);
			this->pn_login->Controls->Add(this->label4);
			this->pn_login->Controls->Add(this->label3);
			this->pn_login->Controls->Add(this->textBox3);
			this->pn_login->Controls->Add(this->textBox2);
			this->pn_login->Controls->Add(this->textBox1);
			this->pn_login->Controls->Add(this->panel1);
			this->pn_login->Controls->Add(this->panel2);
			this->pn_login->Controls->Add(this->label2);
			this->pn_login->Controls->Add(this->pictureBox6);
			this->pn_login->Controls->Add(this->pictureBox7);
			this->pn_login->Dock = System::Windows::Forms::DockStyle::Left;
			this->pn_login->Location = System::Drawing::Point(0, 0);
			this->pn_login->Margin = System::Windows::Forms::Padding(2);
			this->pn_login->Name = L"pn_login";
			this->pn_login->Size = System::Drawing::Size(713, 494);
			this->pn_login->TabIndex = 1;
			// 
			// pictureBox25
			// 
			this->pictureBox25->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox25.Image")));
			this->pictureBox25->Location = System::Drawing::Point(450, 388);
			this->pictureBox25->Name = L"pictureBox25";
			this->pictureBox25->Size = System::Drawing::Size(42, 41);
			this->pictureBox25->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox25->TabIndex = 14;
			this->pictureBox25->TabStop = false;
			// 
			// pictureBox24
			// 
			this->pictureBox24->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox24.Image")));
			this->pictureBox24->Location = System::Drawing::Point(8, 91);
			this->pictureBox24->Name = L"pictureBox24";
			this->pictureBox24->Size = System::Drawing::Size(32, 32);
			this->pictureBox24->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox24->TabIndex = 13;
			this->pictureBox24->TabStop = false;
			// 
			// pictureBox23
			// 
			this->pictureBox23->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox23.Image")));
			this->pictureBox23->Location = System::Drawing::Point(12, 198);
			this->pictureBox23->Name = L"pictureBox23";
			this->pictureBox23->Size = System::Drawing::Size(27, 28);
			this->pictureBox23->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox23->TabIndex = 12;
			this->pictureBox23->TabStop = false;
			// 
			// pictureBox5
			// 
			this->pictureBox5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox5.Image")));
			this->pictureBox5->Location = System::Drawing::Point(526, -2);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(187, 158);
			this->pictureBox5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox5->TabIndex = 2;
			this->pictureBox5->TabStop = false;
			// 
			// label64
			// 
			this->label64->AutoSize = true;
			this->label64->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label64->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label64->ForeColor = System::Drawing::Color::Red;
			this->label64->Location = System::Drawing::Point(48, 263);
			this->label64->Name = L"label64";
			this->label64->Size = System::Drawing::Size(200, 17);
			this->label64->TabIndex = 11;
			this->label64->Text = L"Wrong usename or password !";
			this->label64->Visible = false;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::Black;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->label7->ForeColor = System::Drawing::Color::White;
			this->label7->Location = System::Drawing::Point(493, 398);
			this->label7->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(155, 20);
			this->label7->TabIndex = 10;
			this->label7->Text = L"Don\'t have account\?";
			// 
			// button7
			// 
			this->button7->BackColor = System::Drawing::Color::Black;
			this->button7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button7->ForeColor = System::Drawing::Color::White;
			this->button7->Location = System::Drawing::Point(49, 316);
			this->button7->Margin = System::Windows::Forms::Padding(2);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(200, 41);
			this->button7->TabIndex = 9;
			this->button7->Text = L"Sign In";
			this->button7->UseVisualStyleBackColor = false;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::Color::Black;
			this->button6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button6->ForeColor = System::Drawing::Color::White;
			this->button6->Location = System::Drawing::Point(497, 429);
			this->button6->Margin = System::Windows::Forms::Padding(2);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(146, 30);
			this->button6->TabIndex = 8;
			this->button6->Text = L"Register";
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Black;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(42, 203);
			this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(86, 20);
			this->label4->TabIndex = 5;
			this->label4->Text = L"Password";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Black;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(41, 98);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(91, 20);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Username";
			this->label3->Click += gcnew System::EventHandler(this, &MyForm::label3_Click);
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::Color::Black;
			this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox3->ForeColor = System::Drawing::Color::White;
			this->textBox3->Location = System::Drawing::Point(47, 233);
			this->textBox3->Margin = System::Windows::Forms::Padding(2);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(204, 16);
			this->textBox3->TabIndex = 3;
			this->textBox3->UseSystemPasswordChar = true;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged);
			this->textBox3->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::textBox3_KeyDown);
			this->textBox3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox3_KeyPress);
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::Black;
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->ForeColor = System::Drawing::Color::White;
			this->textBox2->Location = System::Drawing::Point(47, 140);
			this->textBox2->Margin = System::Windows::Forms::Padding(2);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(204, 16);
			this->textBox2->TabIndex = 3;
			this->textBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::textBox2_KeyDown);
			this->textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox2_KeyPress);
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::Black;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->ForeColor = System::Drawing::Color::White;
			this->textBox1->Location = System::Drawing::Point(58, 98);
			this->textBox1->Margin = System::Windows::Forms::Padding(2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(204, 13);
			this->textBox1->TabIndex = 3;
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(47, 157);
			this->panel1->Margin = System::Windows::Forms::Padding(2);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(204, 2);
			this->panel1->TabIndex = 4;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel1_Paint);
			// 
			// panel2
			// 
			this->panel2->Location = System::Drawing::Point(47, 250);
			this->panel2->Margin = System::Windows::Forms::Padding(2);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(204, 2);
			this->panel2->TabIndex = 4;
			this->panel2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel1_Paint);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Black;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(9, 38);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(123, 37);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Sign In";
			// 
			// pictureBox6
			// 
			this->pictureBox6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox6.Image")));
			this->pictureBox6->Location = System::Drawing::Point(0, 0);
			this->pictureBox6->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(714, 494);
			this->pictureBox6->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox6->TabIndex = 0;
			this->pictureBox6->TabStop = false;
			this->pictureBox6->Click += gcnew System::EventHandler(this, &MyForm::pictureBox6_Click);
			// 
			// pictureBox7
			// 
			this->pictureBox7->BackColor = System::Drawing::Color::Black;
			this->pictureBox7->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox7.BackgroundImage")));
			this->pictureBox7->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox7->Location = System::Drawing::Point(0, 405);
			this->pictureBox7->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(97, 87);
			this->pictureBox7->TabIndex = 1;
			this->pictureBox7->TabStop = false;
			// 
			// pn_back
			// 
			this->pn_back->Controls->Add(this->button4);
			this->pn_back->Controls->Add(this->pictureBox22);
			this->pn_back->Dock = System::Windows::Forms::DockStyle::Right;
			this->pn_back->Location = System::Drawing::Point(710, 0);
			this->pn_back->Margin = System::Windows::Forms::Padding(2);
			this->pn_back->Name = L"pn_back";
			this->pn_back->Size = System::Drawing::Size(218, 494);
			this->pn_back->TabIndex = 0;
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::Black;
			this->button4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button4->ForeColor = System::Drawing::Color::White;
			this->button4->Location = System::Drawing::Point(2, 446);
			this->button4->Margin = System::Windows::Forms::Padding(2);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(218, 47);
			this->button4->TabIndex = 1;
			this->button4->Text = L"Back";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// pictureBox22
			// 
			this->pictureBox22->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox22->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox22.Image")));
			this->pictureBox22->Location = System::Drawing::Point(0, 0);
			this->pictureBox22->Name = L"pictureBox22";
			this->pictureBox22->Size = System::Drawing::Size(218, 494);
			this->pictureBox22->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox22->TabIndex = 0;
			this->pictureBox22->TabStop = false;
			// 
			// pn_riderRe
			// 
			this->pn_riderRe->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(166)), static_cast<System::Int32>(static_cast<System::Byte>(166)),
				static_cast<System::Int32>(static_cast<System::Byte>(166)));
			this->pn_riderRe->Controls->Add(this->loading_gifr);
			this->pn_riderRe->Controls->Add(this->progressBar2);
			this->pn_riderRe->Controls->Add(this->rider_r_error);
			this->pn_riderRe->Controls->Add(this->label5);
			this->pn_riderRe->Controls->Add(this->checkBox1);
			this->pn_riderRe->Controls->Add(this->button12);
			this->pn_riderRe->Controls->Add(this->button11);
			this->pn_riderRe->Controls->Add(this->label13);
			this->pn_riderRe->Controls->Add(this->flowLayoutPanel5);
			this->pn_riderRe->Controls->Add(this->textBox8);
			this->pn_riderRe->Controls->Add(this->label12);
			this->pn_riderRe->Controls->Add(this->flowLayoutPanel4);
			this->pn_riderRe->Controls->Add(this->textBox7);
			this->pn_riderRe->Controls->Add(this->label11);
			this->pn_riderRe->Controls->Add(this->flowLayoutPanel3);
			this->pn_riderRe->Controls->Add(this->textBox6);
			this->pn_riderRe->Controls->Add(this->label10);
			this->pn_riderRe->Controls->Add(this->flowLayoutPanel2);
			this->pn_riderRe->Controls->Add(this->textBox5);
			this->pn_riderRe->Controls->Add(this->label9);
			this->pn_riderRe->Controls->Add(this->label8);
			this->pn_riderRe->Controls->Add(this->flowLayoutPanel1);
			this->pn_riderRe->Controls->Add(this->textBox4);
			this->pn_riderRe->Controls->Add(this->pictureBox10);
			this->pn_riderRe->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_riderRe->Location = System::Drawing::Point(0, 34);
			this->pn_riderRe->Margin = System::Windows::Forms::Padding(2);
			this->pn_riderRe->Name = L"pn_riderRe";
			this->pn_riderRe->Size = System::Drawing::Size(928, 494);
			this->pn_riderRe->TabIndex = 2;
			// 
			// loading_gifr
			// 
			this->loading_gifr->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"loading_gifr.Image")));
			this->loading_gifr->Location = System::Drawing::Point(26, 406);
			this->loading_gifr->Margin = System::Windows::Forms::Padding(2);
			this->loading_gifr->Name = L"loading_gifr";
			this->loading_gifr->Size = System::Drawing::Size(60, 41);
			this->loading_gifr->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->loading_gifr->TabIndex = 55;
			this->loading_gifr->TabStop = false;
			this->loading_gifr->Visible = false;
			// 
			// progressBar2
			// 
			this->progressBar2->BackColor = System::Drawing::Color::Black;
			this->progressBar2->ForeColor = System::Drawing::Color::Lime;
			this->progressBar2->Location = System::Drawing::Point(46, 311);
			this->progressBar2->Name = L"progressBar2";
			this->progressBar2->Size = System::Drawing::Size(187, 3);
			this->progressBar2->Step = 4;
			this->progressBar2->TabIndex = 54;
			// 
			// rider_r_error
			// 
			this->rider_r_error->AutoSize = true;
			this->rider_r_error->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(166)), static_cast<System::Int32>(static_cast<System::Byte>(166)),
				static_cast<System::Int32>(static_cast<System::Byte>(166)));
			this->rider_r_error->Cursor = System::Windows::Forms::Cursors::Hand;
			this->rider_r_error->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Underline,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(161)));
			this->rider_r_error->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->rider_r_error->Location = System::Drawing::Point(31, 418);
			this->rider_r_error->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->rider_r_error->Name = L"rider_r_error";
			this->rider_r_error->Size = System::Drawing::Size(40, 18);
			this->rider_r_error->TabIndex = 22;
			this->rider_r_error->Text = L"error";
			this->rider_r_error->Visible = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(166)), static_cast<System::Int32>(static_cast<System::Byte>(166)),
				static_cast<System::Int32>(static_cast<System::Byte>(166)));
			this->label5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::MediumBlue;
			this->label5->Location = System::Drawing::Point(117, 386);
			this->label5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(166, 17);
			this->label5->TabIndex = 21;
			this->label5->Text = L"Terms and Conditions";
			this->label5->Click += gcnew System::EventHandler(this, &MyForm::label5_Click_1);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(166)), static_cast<System::Int32>(static_cast<System::Byte>(166)),
				static_cast<System::Int32>(static_cast<System::Byte>(166)));
			this->checkBox1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->checkBox1->ForeColor = System::Drawing::Color::Black;
			this->checkBox1->Location = System::Drawing::Point(26, 386);
			this->checkBox1->Margin = System::Windows::Forms::Padding(2);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(97, 21);
			this->checkBox1->TabIndex = 20;
			this->checkBox1->Text = L"I agree to";
			this->checkBox1->UseVisualStyleBackColor = false;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged_1);
			// 
			// button12
			// 
			this->button12->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(132)), static_cast<System::Int32>(static_cast<System::Byte>(109)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->button12->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button12->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button12->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(253)), static_cast<System::Int32>(static_cast<System::Byte>(247)),
				static_cast<System::Int32>(static_cast<System::Byte>(242)));
			this->button12->Location = System::Drawing::Point(15, 451);
			this->button12->Margin = System::Windows::Forms::Padding(2);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(217, 32);
			this->button12->TabIndex = 19;
			this->button12->Text = L"Back";
			this->button12->UseVisualStyleBackColor = false;
			this->button12->Click += gcnew System::EventHandler(this, &MyForm::button12_Click);
			// 
			// button11
			// 
			this->button11->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(132)), static_cast<System::Int32>(static_cast<System::Byte>(109)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->button11->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button11->Enabled = false;
			this->button11->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button11->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(253)), static_cast<System::Int32>(static_cast<System::Byte>(247)),
				static_cast<System::Int32>(static_cast<System::Byte>(242)));
			this->button11->Location = System::Drawing::Point(262, 451);
			this->button11->Margin = System::Windows::Forms::Padding(2);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(218, 32);
			this->button11->TabIndex = 18;
			this->button11->Text = L"Register";
			this->button11->UseVisualStyleBackColor = false;
			this->button11->Click += gcnew System::EventHandler(this, &MyForm::button11_Click);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(22, 322);
			this->label13->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(23, 17);
			this->label13->TabIndex = 17;
			this->label13->Text = L"ID";
			// 
			// flowLayoutPanel5
			// 
			this->flowLayoutPanel5->BackColor = System::Drawing::Color::Black;
			this->flowLayoutPanel5->Location = System::Drawing::Point(49, 377);
			this->flowLayoutPanel5->Margin = System::Windows::Forms::Padding(2);
			this->flowLayoutPanel5->Name = L"flowLayoutPanel5";
			this->flowLayoutPanel5->Size = System::Drawing::Size(183, 2);
			this->flowLayoutPanel5->TabIndex = 16;
			// 
			// textBox8
			// 
			this->textBox8->BackColor = System::Drawing::Color::White;
			this->textBox8->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox8->ForeColor = System::Drawing::Color::Black;
			this->textBox8->Location = System::Drawing::Point(47, 358);
			this->textBox8->Margin = System::Windows::Forms::Padding(2);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(184, 16);
			this->textBox8->TabIndex = 15;
			this->textBox8->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox8_KeyPress);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(22, 253);
			this->label12->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(77, 17);
			this->label12->TabIndex = 14;
			this->label12->Text = L"Password";
			// 
			// flowLayoutPanel4
			// 
			this->flowLayoutPanel4->BackColor = System::Drawing::Color::Black;
			this->flowLayoutPanel4->Location = System::Drawing::Point(49, 308);
			this->flowLayoutPanel4->Margin = System::Windows::Forms::Padding(2);
			this->flowLayoutPanel4->Name = L"flowLayoutPanel4";
			this->flowLayoutPanel4->Size = System::Drawing::Size(183, 2);
			this->flowLayoutPanel4->TabIndex = 13;
			// 
			// textBox7
			// 
			this->textBox7->BackColor = System::Drawing::Color::White;
			this->textBox7->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox7->ForeColor = System::Drawing::Color::Black;
			this->textBox7->Location = System::Drawing::Point(47, 289);
			this->textBox7->Margin = System::Windows::Forms::Padding(2);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(184, 16);
			this->textBox7->TabIndex = 12;
			this->textBox7->UseSystemPasswordChar = true;
			this->textBox7->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox7_TextChanged);
			this->textBox7->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox7_KeyPress);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(22, 184);
			this->label11->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(81, 17);
			this->label11->TabIndex = 11;
			this->label11->Text = L"Username";
			// 
			// flowLayoutPanel3
			// 
			this->flowLayoutPanel3->BackColor = System::Drawing::Color::Black;
			this->flowLayoutPanel3->Location = System::Drawing::Point(49, 239);
			this->flowLayoutPanel3->Margin = System::Windows::Forms::Padding(2);
			this->flowLayoutPanel3->Name = L"flowLayoutPanel3";
			this->flowLayoutPanel3->Size = System::Drawing::Size(183, 2);
			this->flowLayoutPanel3->TabIndex = 10;
			// 
			// textBox6
			// 
			this->textBox6->BackColor = System::Drawing::Color::White;
			this->textBox6->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox6->ForeColor = System::Drawing::Color::Black;
			this->textBox6->Location = System::Drawing::Point(47, 219);
			this->textBox6->Margin = System::Windows::Forms::Padding(2);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(184, 16);
			this->textBox6->TabIndex = 9;
			this->textBox6->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox6_KeyPress);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(22, 115);
			this->label10->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(78, 17);
			this->label10->TabIndex = 8;
			this->label10->Text = L"last name";
			this->label10->Click += gcnew System::EventHandler(this, &MyForm::label10_Click);
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->BackColor = System::Drawing::Color::Black;
			this->flowLayoutPanel2->Location = System::Drawing::Point(49, 170);
			this->flowLayoutPanel2->Margin = System::Windows::Forms::Padding(2);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Size = System::Drawing::Size(183, 2);
			this->flowLayoutPanel2->TabIndex = 7;
			this->flowLayoutPanel2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::flowLayoutPanel2_Paint);
			// 
			// textBox5
			// 
			this->textBox5->BackColor = System::Drawing::Color::White;
			this->textBox5->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox5->ForeColor = System::Drawing::Color::Black;
			this->textBox5->Location = System::Drawing::Point(47, 150);
			this->textBox5->Margin = System::Windows::Forms::Padding(2);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(184, 16);
			this->textBox5->TabIndex = 6;
			this->textBox5->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox5_TextChanged);
			this->textBox5->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox5_KeyPress);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(22, 46);
			this->label9->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(84, 17);
			this->label9->TabIndex = 5;
			this->label9->Text = L"First name";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(9, 15);
			this->label8->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(263, 24);
			this->label8->TabIndex = 4;
			this->label8->Text = L"Please enter the following :";
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->BackColor = System::Drawing::Color::Black;
			this->flowLayoutPanel1->Location = System::Drawing::Point(49, 101);
			this->flowLayoutPanel1->Margin = System::Windows::Forms::Padding(2);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(183, 2);
			this->flowLayoutPanel1->TabIndex = 3;
			// 
			// textBox4
			// 
			this->textBox4->BackColor = System::Drawing::Color::White;
			this->textBox4->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox4->ForeColor = System::Drawing::Color::Black;
			this->textBox4->Location = System::Drawing::Point(47, 81);
			this->textBox4->Margin = System::Windows::Forms::Padding(2);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(184, 16);
			this->textBox4->TabIndex = 2;
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox4_TextChanged);
			this->textBox4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox4_KeyPress);
			// 
			// pictureBox10
			// 
			this->pictureBox10->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->pictureBox10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(253)), static_cast<System::Int32>(static_cast<System::Byte>(247)),
				static_cast<System::Int32>(static_cast<System::Byte>(242)));
			this->pictureBox10->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox10.Image")));
			this->pictureBox10->Location = System::Drawing::Point(494, 0);
			this->pictureBox10->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->Size = System::Drawing::Size(409, 494);
			this->pictureBox10->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox10->TabIndex = 0;
			this->pictureBox10->TabStop = false;
			this->pictureBox10->Click += gcnew System::EventHandler(this, &MyForm::pictureBox10_Click);
			// 
			// pn_captinRe
			// 
			this->pn_captinRe->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(166)), static_cast<System::Int32>(static_cast<System::Byte>(166)),
				static_cast<System::Int32>(static_cast<System::Byte>(166)));
			this->pn_captinRe->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pn_captinRe->Controls->Add(this->loading_gifc);
			this->pn_captinRe->Controls->Add(this->progressBar1);
			this->pn_captinRe->Controls->Add(this->captain_r_error);
			this->pn_captinRe->Controls->Add(this->label73);
			this->pn_captinRe->Controls->Add(this->label25);
			this->pn_captinRe->Controls->Add(this->checkBox2);
			this->pn_captinRe->Controls->Add(this->flowLayoutPanel13);
			this->pn_captinRe->Controls->Add(this->textBox14);
			this->pn_captinRe->Controls->Add(this->label23);
			this->pn_captinRe->Controls->Add(this->label22);
			this->pn_captinRe->Controls->Add(this->flowLayoutPanel15);
			this->pn_captinRe->Controls->Add(this->flowLayoutPanel14);
			this->pn_captinRe->Controls->Add(this->flowLayoutPanel12);
			this->pn_captinRe->Controls->Add(this->comboBox12);
			this->pn_captinRe->Controls->Add(this->comboBox11);
			this->pn_captinRe->Controls->Add(this->comboBox2);
			this->pn_captinRe->Controls->Add(this->label21);
			this->pn_captinRe->Controls->Add(this->comboBox1);
			this->pn_captinRe->Controls->Add(this->flowLayoutPanel11);
			this->pn_captinRe->Controls->Add(this->label20);
			this->pn_captinRe->Controls->Add(this->button14);
			this->pn_captinRe->Controls->Add(this->button13);
			this->pn_captinRe->Controls->Add(this->label19);
			this->pn_captinRe->Controls->Add(this->flowLayoutPanel6);
			this->pn_captinRe->Controls->Add(this->textBox9);
			this->pn_captinRe->Controls->Add(this->label14);
			this->pn_captinRe->Controls->Add(this->flowLayoutPanel7);
			this->pn_captinRe->Controls->Add(this->textBox10);
			this->pn_captinRe->Controls->Add(this->label15);
			this->pn_captinRe->Controls->Add(this->flowLayoutPanel8);
			this->pn_captinRe->Controls->Add(this->textBox11);
			this->pn_captinRe->Controls->Add(this->label16);
			this->pn_captinRe->Controls->Add(this->flowLayoutPanel9);
			this->pn_captinRe->Controls->Add(this->textBox12);
			this->pn_captinRe->Controls->Add(this->label17);
			this->pn_captinRe->Controls->Add(this->label18);
			this->pn_captinRe->Controls->Add(this->flowLayoutPanel10);
			this->pn_captinRe->Controls->Add(this->textBox13);
			this->pn_captinRe->Controls->Add(this->pictureBox11);
			this->pn_captinRe->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_captinRe->Location = System::Drawing::Point(0, 34);
			this->pn_captinRe->Margin = System::Windows::Forms::Padding(2);
			this->pn_captinRe->Name = L"pn_captinRe";
			this->pn_captinRe->Size = System::Drawing::Size(928, 494);
			this->pn_captinRe->TabIndex = 22;
			// 
			// loading_gifc
			// 
			this->loading_gifc->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"loading_gifc.Image")));
			this->loading_gifc->Location = System::Drawing::Point(21, 407);
			this->loading_gifc->Margin = System::Windows::Forms::Padding(2);
			this->loading_gifc->Name = L"loading_gifc";
			this->loading_gifc->Size = System::Drawing::Size(60, 41);
			this->loading_gifc->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->loading_gifc->TabIndex = 56;
			this->loading_gifc->TabStop = false;
			this->loading_gifc->Visible = false;
			// 
			// progressBar1
			// 
			this->progressBar1->BackColor = System::Drawing::Color::Black;
			this->progressBar1->ForeColor = System::Drawing::Color::Lime;
			this->progressBar1->Location = System::Drawing::Point(39, 309);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(187, 3);
			this->progressBar1->Step = 4;
			this->progressBar1->TabIndex = 53;
			// 
			// captain_r_error
			// 
			this->captain_r_error->AutoSize = true;
			this->captain_r_error->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(166)), static_cast<System::Int32>(static_cast<System::Byte>(166)),
				static_cast<System::Int32>(static_cast<System::Byte>(166)));
			this->captain_r_error->Cursor = System::Windows::Forms::Cursors::Hand;
			this->captain_r_error->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->captain_r_error->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->captain_r_error->Location = System::Drawing::Point(24, 414);
			this->captain_r_error->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->captain_r_error->Name = L"captain_r_error";
			this->captain_r_error->Size = System::Drawing::Size(39, 17);
			this->captain_r_error->TabIndex = 52;
			this->captain_r_error->Text = L"error";
			this->captain_r_error->Visible = false;
			// 
			// label73
			// 
			this->label73->AutoSize = true;
			this->label73->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label73->Location = System::Drawing::Point(249, 330);
			this->label73->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label73->Name = L"label73";
			this->label73->Size = System::Drawing::Size(97, 17);
			this->label73->TabIndex = 51;
			this->label73->Text = L"City location";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(166)), static_cast<System::Int32>(static_cast<System::Byte>(166)),
				static_cast<System::Int32>(static_cast<System::Byte>(166)));
			this->label25->Cursor = System::Windows::Forms::Cursors::Hand;
			this->label25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label25->ForeColor = System::Drawing::Color::MediumBlue;
			this->label25->Location = System::Drawing::Point(112, 385);
			this->label25->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(166, 17);
			this->label25->TabIndex = 50;
			this->label25->Text = L"Terms and Conditions";
			this->label25->Click += gcnew System::EventHandler(this, &MyForm::label25_Click);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(166)), static_cast<System::Int32>(static_cast<System::Byte>(166)),
				static_cast<System::Int32>(static_cast<System::Byte>(166)));
			this->checkBox2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->checkBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->checkBox2->ForeColor = System::Drawing::Color::Black;
			this->checkBox2->Location = System::Drawing::Point(21, 385);
			this->checkBox2->Margin = System::Windows::Forms::Padding(2);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(97, 21);
			this->checkBox2->TabIndex = 49;
			this->checkBox2->Text = L"I agree to";
			this->checkBox2->UseVisualStyleBackColor = false;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox2_CheckedChanged);
			// 
			// flowLayoutPanel13
			// 
			this->flowLayoutPanel13->BackColor = System::Drawing::Color::Black;
			this->flowLayoutPanel13->Location = System::Drawing::Point(269, 305);
			this->flowLayoutPanel13->Margin = System::Windows::Forms::Padding(2);
			this->flowLayoutPanel13->Name = L"flowLayoutPanel13";
			this->flowLayoutPanel13->Size = System::Drawing::Size(183, 2);
			this->flowLayoutPanel13->TabIndex = 48;
			// 
			// textBox14
			// 
			this->textBox14->BackColor = System::Drawing::Color::WhiteSmoke;
			this->textBox14->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox14->ForeColor = System::Drawing::Color::Black;
			this->textBox14->Location = System::Drawing::Point(268, 287);
			this->textBox14->Margin = System::Windows::Forms::Padding(2);
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(185, 16);
			this->textBox14->TabIndex = 47;
			this->textBox14->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox14_KeyPress);
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label23->Location = System::Drawing::Point(242, 256);
			this->label23->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(94, 17);
			this->label23->TabIndex = 46;
			this->label23->Text = L"Car Number";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label22->Location = System::Drawing::Point(242, 186);
			this->label22->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(77, 17);
			this->label22->TabIndex = 42;
			this->label22->Text = L"Car Level";
			// 
			// flowLayoutPanel15
			// 
			this->flowLayoutPanel15->BackColor = System::Drawing::Color::Black;
			this->flowLayoutPanel15->Location = System::Drawing::Point(268, 379);
			this->flowLayoutPanel15->Margin = System::Windows::Forms::Padding(2);
			this->flowLayoutPanel15->Name = L"flowLayoutPanel15";
			this->flowLayoutPanel15->Size = System::Drawing::Size(183, 2);
			this->flowLayoutPanel15->TabIndex = 41;
			// 
			// flowLayoutPanel14
			// 
			this->flowLayoutPanel14->BackColor = System::Drawing::Color::Black;
			this->flowLayoutPanel14->Location = System::Drawing::Point(268, 240);
			this->flowLayoutPanel14->Margin = System::Windows::Forms::Padding(2);
			this->flowLayoutPanel14->Name = L"flowLayoutPanel14";
			this->flowLayoutPanel14->Size = System::Drawing::Size(183, 2);
			this->flowLayoutPanel14->TabIndex = 41;
			// 
			// flowLayoutPanel12
			// 
			this->flowLayoutPanel12->BackColor = System::Drawing::Color::Black;
			this->flowLayoutPanel12->Location = System::Drawing::Point(268, 167);
			this->flowLayoutPanel12->Margin = System::Windows::Forms::Padding(2);
			this->flowLayoutPanel12->Name = L"flowLayoutPanel12";
			this->flowLayoutPanel12->Size = System::Drawing::Size(183, 2);
			this->flowLayoutPanel12->TabIndex = 41;
			// 
			// comboBox12
			// 
			this->comboBox12->BackColor = System::Drawing::Color::WhiteSmoke;
			this->comboBox12->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox12->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->comboBox12->FormattingEnabled = true;
			this->comboBox12->Items->AddRange(gcnew cli::array< System::Object^  >(27) {
				L"Alexandria", L"Aswan", L"Assiut", L"Beheira",
					L"Beni Suef", L"Cairo", L"Dakahlia", L"Damietta", L"Faiyum", L"Gharbia", L"Giza", L"Ismailia", L"Kafr El Sheikh", L"Luxor", L"Matrouh",
					L"Minya", L"Monufia", L"New Valley", L"North Sinai", L"Port Said", L"Qalyubia", L"Qena", L"Red Sea", L"Sharqia", L"Sohag", L"South Sinai",
					L"Suez"
			});
			this->comboBox12->Location = System::Drawing::Point(267, 355);
			this->comboBox12->Margin = System::Windows::Forms::Padding(2);
			this->comboBox12->Name = L"comboBox12";
			this->comboBox12->Size = System::Drawing::Size(184, 21);
			this->comboBox12->TabIndex = 40;
			// 
			// comboBox11
			// 
			this->comboBox11->BackColor = System::Drawing::Color::WhiteSmoke;
			this->comboBox11->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox11->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->comboBox11->FormattingEnabled = true;
			this->comboBox11->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Level 1", L"Level 2", L"Level 3" });
			this->comboBox11->Location = System::Drawing::Point(267, 216);
			this->comboBox11->Margin = System::Windows::Forms::Padding(2);
			this->comboBox11->Name = L"comboBox11";
			this->comboBox11->Size = System::Drawing::Size(184, 21);
			this->comboBox11->TabIndex = 40;
			// 
			// comboBox2
			// 
			this->comboBox2->BackColor = System::Drawing::Color::WhiteSmoke;
			this->comboBox2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox2->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(16) {
				L"Black", L"White", L"Blue", L"Yellow", L"Red",
					L"Green", L"Orange", L"Brown", L"Olive", L"Grey", L"Purple", L"Silver", L"Pink", L"Cyan", L"Rust", L"Sky"
			});
			this->comboBox2->Location = System::Drawing::Point(267, 143);
			this->comboBox2->Margin = System::Windows::Forms::Padding(2);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(184, 21);
			this->comboBox2->TabIndex = 40;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label21->Location = System::Drawing::Point(242, 115);
			this->label21->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(76, 17);
			this->label21->TabIndex = 39;
			this->label21->Text = L"Car Color";
			// 
			// comboBox1
			// 
			this->comboBox1->BackColor = System::Drawing::Color::WhiteSmoke;
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(14) {
				L"KIA", L"Audi", L"BMW", L"MITSUBISHI", L"HYUNDAI",
					L"NISSAN", L"CHERY", L"Mercedes", L"Skoda", L"FIAT", L"HONDA", L"TOYOTA", L"CHEVROLET", L"LADA"
			});
			this->comboBox1->Location = System::Drawing::Point(270, 73);
			this->comboBox1->Margin = System::Windows::Forms::Padding(2);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(184, 21);
			this->comboBox1->TabIndex = 38;
			// 
			// flowLayoutPanel11
			// 
			this->flowLayoutPanel11->BackColor = System::Drawing::Color::Black;
			this->flowLayoutPanel11->Location = System::Drawing::Point(270, 97);
			this->flowLayoutPanel11->Margin = System::Windows::Forms::Padding(2);
			this->flowLayoutPanel11->Name = L"flowLayoutPanel11";
			this->flowLayoutPanel11->Size = System::Drawing::Size(183, 2);
			this->flowLayoutPanel11->TabIndex = 37;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label20->Location = System::Drawing::Point(242, 48);
			this->label20->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(74, 17);
			this->label20->TabIndex = 35;
			this->label20->Text = L"Car Type";
			// 
			// button14
			// 
			this->button14->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(132)), static_cast<System::Int32>(static_cast<System::Byte>(109)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->button14->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button14->Enabled = false;
			this->button14->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button14->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(253)), static_cast<System::Int32>(static_cast<System::Byte>(247)),
				static_cast<System::Int32>(static_cast<System::Byte>(242)));
			this->button14->Location = System::Drawing::Point(248, 453);
			this->button14->Margin = System::Windows::Forms::Padding(2);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(220, 32);
			this->button14->TabIndex = 34;
			this->button14->Text = L"Register";
			this->button14->UseVisualStyleBackColor = false;
			this->button14->Click += gcnew System::EventHandler(this, &MyForm::button14_Click);
			// 
			// button13
			// 
			this->button13->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(132)), static_cast<System::Int32>(static_cast<System::Byte>(109)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->button13->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button13->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button13->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(253)), static_cast<System::Int32>(static_cast<System::Byte>(247)),
				static_cast<System::Int32>(static_cast<System::Byte>(242)));
			this->button13->Location = System::Drawing::Point(9, 453);
			this->button13->Margin = System::Windows::Forms::Padding(2);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(217, 32);
			this->button13->TabIndex = 33;
			this->button13->Text = L"Back";
			this->button13->UseVisualStyleBackColor = false;
			this->button13->Click += gcnew System::EventHandler(this, &MyForm::button13_Click);
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label19->Location = System::Drawing::Point(15, 329);
			this->label19->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(23, 17);
			this->label19->TabIndex = 32;
			this->label19->Text = L"ID";
			// 
			// flowLayoutPanel6
			// 
			this->flowLayoutPanel6->BackColor = System::Drawing::Color::Black;
			this->flowLayoutPanel6->Location = System::Drawing::Point(41, 375);
			this->flowLayoutPanel6->Margin = System::Windows::Forms::Padding(2);
			this->flowLayoutPanel6->Name = L"flowLayoutPanel6";
			this->flowLayoutPanel6->Size = System::Drawing::Size(183, 2);
			this->flowLayoutPanel6->TabIndex = 31;
			// 
			// textBox9
			// 
			this->textBox9->BackColor = System::Drawing::Color::WhiteSmoke;
			this->textBox9->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox9->ForeColor = System::Drawing::Color::Black;
			this->textBox9->Location = System::Drawing::Point(40, 356);
			this->textBox9->Margin = System::Windows::Forms::Padding(2);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(185, 16);
			this->textBox9->TabIndex = 30;
			this->textBox9->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox9_KeyPress);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->Location = System::Drawing::Point(15, 251);
			this->label14->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(77, 17);
			this->label14->TabIndex = 29;
			this->label14->Text = L"Password";
			// 
			// flowLayoutPanel7
			// 
			this->flowLayoutPanel7->BackColor = System::Drawing::Color::Black;
			this->flowLayoutPanel7->Location = System::Drawing::Point(41, 306);
			this->flowLayoutPanel7->Margin = System::Windows::Forms::Padding(2);
			this->flowLayoutPanel7->Name = L"flowLayoutPanel7";
			this->flowLayoutPanel7->Size = System::Drawing::Size(183, 2);
			this->flowLayoutPanel7->TabIndex = 28;
			// 
			// textBox10
			// 
			this->textBox10->BackColor = System::Drawing::Color::WhiteSmoke;
			this->textBox10->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox10->ForeColor = System::Drawing::Color::Black;
			this->textBox10->Location = System::Drawing::Point(40, 287);
			this->textBox10->Margin = System::Windows::Forms::Padding(2);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(185, 16);
			this->textBox10->TabIndex = 27;
			this->textBox10->UseSystemPasswordChar = true;
			this->textBox10->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox10_TextChanged);
			this->textBox10->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox10_KeyPress);
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(15, 182);
			this->label15->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(81, 17);
			this->label15->TabIndex = 26;
			this->label15->Text = L"Username";
			// 
			// flowLayoutPanel8
			// 
			this->flowLayoutPanel8->BackColor = System::Drawing::Color::Black;
			this->flowLayoutPanel8->Location = System::Drawing::Point(41, 237);
			this->flowLayoutPanel8->Margin = System::Windows::Forms::Padding(2);
			this->flowLayoutPanel8->Name = L"flowLayoutPanel8";
			this->flowLayoutPanel8->Size = System::Drawing::Size(183, 2);
			this->flowLayoutPanel8->TabIndex = 25;
			// 
			// textBox11
			// 
			this->textBox11->BackColor = System::Drawing::Color::WhiteSmoke;
			this->textBox11->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox11->ForeColor = System::Drawing::Color::Black;
			this->textBox11->Location = System::Drawing::Point(40, 218);
			this->textBox11->Margin = System::Windows::Forms::Padding(2);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(185, 16);
			this->textBox11->TabIndex = 24;
			this->textBox11->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox11_KeyPress);
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->Location = System::Drawing::Point(15, 113);
			this->label16->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(78, 17);
			this->label16->TabIndex = 23;
			this->label16->Text = L"last name";
			// 
			// flowLayoutPanel9
			// 
			this->flowLayoutPanel9->BackColor = System::Drawing::Color::Black;
			this->flowLayoutPanel9->Location = System::Drawing::Point(41, 165);
			this->flowLayoutPanel9->Margin = System::Windows::Forms::Padding(2);
			this->flowLayoutPanel9->Name = L"flowLayoutPanel9";
			this->flowLayoutPanel9->Size = System::Drawing::Size(183, 2);
			this->flowLayoutPanel9->TabIndex = 22;
			// 
			// textBox12
			// 
			this->textBox12->BackColor = System::Drawing::Color::WhiteSmoke;
			this->textBox12->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox12->ForeColor = System::Drawing::Color::Black;
			this->textBox12->Location = System::Drawing::Point(40, 145);
			this->textBox12->Margin = System::Windows::Forms::Padding(2);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(185, 16);
			this->textBox12->TabIndex = 21;
			this->textBox12->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox12_KeyPress);
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->Location = System::Drawing::Point(15, 44);
			this->label17->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(84, 17);
			this->label17->TabIndex = 20;
			this->label17->Text = L"First name";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label18->Location = System::Drawing::Point(11, 15);
			this->label18->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(263, 24);
			this->label18->TabIndex = 19;
			this->label18->Text = L"Please enter the following :";
			// 
			// flowLayoutPanel10
			// 
			this->flowLayoutPanel10->BackColor = System::Drawing::Color::Black;
			this->flowLayoutPanel10->Location = System::Drawing::Point(41, 96);
			this->flowLayoutPanel10->Margin = System::Windows::Forms::Padding(2);
			this->flowLayoutPanel10->Name = L"flowLayoutPanel10";
			this->flowLayoutPanel10->Size = System::Drawing::Size(183, 2);
			this->flowLayoutPanel10->TabIndex = 18;
			// 
			// textBox13
			// 
			this->textBox13->BackColor = System::Drawing::Color::WhiteSmoke;
			this->textBox13->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox13->ForeColor = System::Drawing::Color::Black;
			this->textBox13->Location = System::Drawing::Point(40, 76);
			this->textBox13->Margin = System::Windows::Forms::Padding(2);
			this->textBox13->Name = L"textBox13";
			this->textBox13->Size = System::Drawing::Size(185, 16);
			this->textBox13->TabIndex = 17;
			this->textBox13->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox13_TextChanged);
			this->textBox13->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox13_KeyPress);
			// 
			// pictureBox11
			// 
			this->pictureBox11->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(166)), static_cast<System::Int32>(static_cast<System::Byte>(166)),
				static_cast<System::Int32>(static_cast<System::Byte>(166)));
			this->pictureBox11->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox11.BackgroundImage")));
			this->pictureBox11->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pictureBox11->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox11.Image")));
			this->pictureBox11->Location = System::Drawing::Point(483, 0);
			this->pictureBox11->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox11->Name = L"pictureBox11";
			this->pictureBox11->Size = System::Drawing::Size(444, 494);
			this->pictureBox11->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox11->TabIndex = 0;
			this->pictureBox11->TabStop = false;
			// 
			// pn_terms
			// 
			this->pn_terms->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->pn_terms->Controls->Add(this->button5);
			this->pn_terms->Controls->Add(this->label6);
			this->pn_terms->Controls->Add(this->richTextBox1);
			this->pn_terms->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_terms->Location = System::Drawing::Point(0, 34);
			this->pn_terms->Margin = System::Windows::Forms::Padding(2);
			this->pn_terms->Name = L"pn_terms";
			this->pn_terms->Size = System::Drawing::Size(928, 494);
			this->pn_terms->TabIndex = 8;
			this->pn_terms->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_terms_Paint);
			// 
			// button5
			// 
			this->button5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button5->BackColor = System::Drawing::Color::DimGray;
			this->button5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button5->ForeColor = System::Drawing::Color::White;
			this->button5->Location = System::Drawing::Point(55, 426);
			this->button5->Margin = System::Windows::Forms::Padding(2);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(118, 32);
			this->button5->TabIndex = 2;
			this->button5->Text = L"Ok";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->label6->Location = System::Drawing::Point(50, 23);
			this->label6->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(352, 37);
			this->label6->TabIndex = 1;
			this->label6->Text = L"Terms and Conditions";
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::Color::DarkGray;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
			this->richTextBox1->Location = System::Drawing::Point(57, 64);
			this->richTextBox1->Margin = System::Windows::Forms::Padding(2);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(807, 352);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = resources->GetString(L"richTextBox1.Text");
			// 
			// pn_terms2
			// 
			this->pn_terms2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->pn_terms2->Controls->Add(this->button15);
			this->pn_terms2->Controls->Add(this->label24);
			this->pn_terms2->Controls->Add(this->richTextBox2);
			this->pn_terms2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_terms2->Location = System::Drawing::Point(0, 34);
			this->pn_terms2->Margin = System::Windows::Forms::Padding(2);
			this->pn_terms2->Name = L"pn_terms2";
			this->pn_terms2->Size = System::Drawing::Size(928, 494);
			this->pn_terms2->TabIndex = 23;
			// 
			// button15
			// 
			this->button15->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button15->BackColor = System::Drawing::Color::DimGray;
			this->button15->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button15->ForeColor = System::Drawing::Color::White;
			this->button15->Location = System::Drawing::Point(52, 424);
			this->button15->Margin = System::Windows::Forms::Padding(2);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(118, 32);
			this->button15->TabIndex = 2;
			this->button15->Text = L"Ok";
			this->button15->UseVisualStyleBackColor = false;
			this->button15->Click += gcnew System::EventHandler(this, &MyForm::button15_Click);
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label24->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->label24->Location = System::Drawing::Point(47, 24);
			this->label24->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(352, 37);
			this->label24->TabIndex = 1;
			this->label24->Text = L"Terms and Conditions";
			// 
			// richTextBox2
			// 
			this->richTextBox2->BackColor = System::Drawing::Color::DarkGray;
			this->richTextBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->richTextBox2->Location = System::Drawing::Point(54, 64);
			this->richTextBox2->Margin = System::Windows::Forms::Padding(2);
			this->richTextBox2->Name = L"richTextBox2";
			this->richTextBox2->ReadOnly = true;
			this->richTextBox2->Size = System::Drawing::Size(811, 352);
			this->richTextBox2->TabIndex = 0;
			this->richTextBox2->Text = resources->GetString(L"richTextBox2.Text");
			// 
			// pn_Register
			// 
			this->pn_Register->Controls->Add(this->button10);
			this->pn_Register->Controls->Add(this->button9);
			this->pn_Register->Controls->Add(this->button8);
			this->pn_Register->Controls->Add(this->pictureBox9);
			this->pn_Register->Controls->Add(this->pictureBox8);
			this->pn_Register->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_Register->Location = System::Drawing::Point(0, 34);
			this->pn_Register->Margin = System::Windows::Forms::Padding(2);
			this->pn_Register->Name = L"pn_Register";
			this->pn_Register->Size = System::Drawing::Size(928, 494);
			this->pn_Register->TabIndex = 11;
			// 
			// button10
			// 
			this->button10->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button10->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button10->Location = System::Drawing::Point(800, 451);
			this->button10->Margin = System::Windows::Forms::Padding(2);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(119, 34);
			this->button10->TabIndex = 4;
			this->button10->Text = L"Back";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &MyForm::button10_Click);
			// 
			// button9
			// 
			this->button9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button9->Location = System::Drawing::Point(616, 297);
			this->button9->Margin = System::Windows::Forms::Padding(2);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(266, 39);
			this->button9->TabIndex = 3;
			this->button9->Text = L"Continue as a Captain";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MyForm::button9_Click);
			// 
			// button8
			// 
			this->button8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button8->Location = System::Drawing::Point(616, 203);
			this->button8->Margin = System::Windows::Forms::Padding(2);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(266, 38);
			this->button8->TabIndex = 2;
			this->button8->Text = L"Continue as a Rider";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MyForm::button8_Click);
			// 
			// pictureBox9
			// 
			this->pictureBox9->BackColor = System::Drawing::Color::White;
			this->pictureBox9->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox9.BackgroundImage")));
			this->pictureBox9->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox9.Image")));
			this->pictureBox9->Location = System::Drawing::Point(563, 0);
			this->pictureBox9->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->Size = System::Drawing::Size(367, 494);
			this->pictureBox9->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox9->TabIndex = 1;
			this->pictureBox9->TabStop = false;
			// 
			// pictureBox8
			// 
			this->pictureBox8->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pictureBox8->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox8.Image")));
			this->pictureBox8->Location = System::Drawing::Point(0, 0);
			this->pictureBox8->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(564, 494);
			this->pictureBox8->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox8->TabIndex = 0;
			this->pictureBox8->TabStop = false;
			// 
			// pn_start
			// 
			this->pn_start->Controls->Add(this->pn_GIF);
			this->pn_start->Controls->Add(this->pn_GIF2);
			this->pn_start->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_start->Location = System::Drawing::Point(0, 34);
			this->pn_start->Margin = System::Windows::Forms::Padding(2);
			this->pn_start->Name = L"pn_start";
			this->pn_start->Size = System::Drawing::Size(928, 494);
			this->pn_start->TabIndex = 1;
			// 
			// pn_GIF
			// 
			this->pn_GIF->Controls->Add(this->button21);
			this->pn_GIF->Controls->Add(this->button2);
			this->pn_GIF->Controls->Add(this->pictureBox1);
			this->pn_GIF->Dock = System::Windows::Forms::DockStyle::Right;
			this->pn_GIF->Location = System::Drawing::Point(179, 0);
			this->pn_GIF->Margin = System::Windows::Forms::Padding(2);
			this->pn_GIF->Name = L"pn_GIF";
			this->pn_GIF->Size = System::Drawing::Size(749, 494);
			this->pn_GIF->TabIndex = 1;
			// 
			// button21
			// 
			this->button21->BackColor = System::Drawing::Color::White;
			this->button21->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button21->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button21->Location = System::Drawing::Point(27, 431);
			this->button21->Margin = System::Windows::Forms::Padding(2);
			this->button21->Name = L"button21";
			this->button21->Size = System::Drawing::Size(178, 40);
			this->button21->TabIndex = 2;
			this->button21->Text = L"Exit";
			this->button21->UseVisualStyleBackColor = false;
			this->button21->Click += gcnew System::EventHandler(this, &MyForm::button21_Click);
			// 
			// button2
			// 
			this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button2->BackColor = System::Drawing::Color::White;
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(546, 426);
			this->button2->Margin = System::Windows::Forms::Padding(2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(178, 40);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Start";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click_1);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(748, 494);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// pn_GIF2
			// 
			this->pn_GIF2->BackColor = System::Drawing::Color::White;
			this->pn_GIF2->Controls->Add(this->pictureBox3);
			this->pn_GIF2->Controls->Add(this->pictureBox2);
			this->pn_GIF2->Dock = System::Windows::Forms::DockStyle::Left;
			this->pn_GIF2->Location = System::Drawing::Point(0, 0);
			this->pn_GIF2->Margin = System::Windows::Forms::Padding(2);
			this->pn_GIF2->Name = L"pn_GIF2";
			this->pn_GIF2->Size = System::Drawing::Size(179, 494);
			this->pn_GIF2->TabIndex = 0;
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.BackgroundImage")));
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(0, 190);
			this->pictureBox3->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(179, 304);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox3->TabIndex = 2;
			this->pictureBox3->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(0, 0);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(179, 193);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			// 
			// pn_bar
			// 
			this->pn_bar->BackColor = System::Drawing::Color::WhiteSmoke;
			this->pn_bar->Controls->Add(this->pictureBox4);
			this->pn_bar->Controls->Add(this->label1);
			this->pn_bar->Controls->Add(this->button3);
			this->pn_bar->Controls->Add(this->button1);
			this->pn_bar->Dock = System::Windows::Forms::DockStyle::Top;
			this->pn_bar->Location = System::Drawing::Point(0, 0);
			this->pn_bar->Margin = System::Windows::Forms::Padding(2);
			this->pn_bar->Name = L"pn_bar";
			this->pn_bar->Size = System::Drawing::Size(928, 34);
			this->pn_bar->TabIndex = 0;
			this->pn_bar->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_bar_Paint);
			this->pn_bar->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pn_bar_MouseDown);
			this->pn_bar->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pn_bar_MouseMove);
			this->pn_bar->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pn_bar_MouseUp);
			// 
			// pictureBox4
			// 
			this->pictureBox4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(2, 1);
			this->pictureBox4->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(38, 32);
			this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox4->TabIndex = 2;
			this->pictureBox4->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::DimGray;
			this->label1->Location = System::Drawing::Point(42, 11);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(57, 15);
			this->label1->TabIndex = 3;
			this->label1->Text = L"UBER +";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// button3
			// 
			this->button3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button3.BackgroundImage")));
			this->button3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button3->FlatAppearance->BorderColor = System::Drawing::Color::Gray;
			this->button3->FlatAppearance->BorderSize = 0;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Location = System::Drawing::Point(846, 0);
			this->button3->Margin = System::Windows::Forms::Padding(2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(38, 34);
			this->button3->TabIndex = 2;
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.BackgroundImage")));
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::Gray;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(887, 1);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(39, 33);
			this->button1->TabIndex = 0;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// pictureBox21
			// 
			this->pictureBox21->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox21->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox21.Image")));
			this->pictureBox21->Location = System::Drawing::Point(0, 0);
			this->pictureBox21->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox21->Name = L"pictureBox21";
			this->pictureBox21->Size = System::Drawing::Size(928, 528);
			this->pictureBox21->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox21->TabIndex = 3;
			this->pictureBox21->TabStop = false;
			// 
			// timer2
			// 
			this->timer2->Interval = 1000;
			this->timer2->Tick += gcnew System::EventHandler(this, &MyForm::timer2_Tick);
			// 
			// clock
			// 
			this->clock->Tick += gcnew System::EventHandler(this, &MyForm::clock_Tick);
			// 
			// status_timer
			// 
			this->status_timer->Interval = 1000;
			// 
			// loading_timer
			// 
			this->loading_timer->Tick += gcnew System::EventHandler(this, &MyForm::loading_timer_Tick);
			// 
			// refreshing_timer
			// 
			this->refreshing_timer->Interval = 1000;
			this->refreshing_timer->Tick += gcnew System::EventHandler(this, &MyForm::refreshing_timer_Tick);
			// 
			// Ride_timer
			// 
			this->Ride_timer->Interval = 1000;
			this->Ride_timer->Tick += gcnew System::EventHandler(this, &MyForm::Ride_timer_Tick);
			// 
			// check_schedule_timer
			// 
			this->check_schedule_timer->Tick += gcnew System::EventHandler(this, &MyForm::check_schedule_timer_Tick);
			// 
			// rider_search_timer
			// 
			this->rider_search_timer->Interval = 1000;
			this->rider_search_timer->Tick += gcnew System::EventHandler(this, &MyForm::rider_search_timer_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(928, 528);
			this->Controls->Add(this->pn_main);
			this->Controls->Add(this->pictureBox21);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->pn_main->ResumeLayout(false);
			this->pn_riderMenu->ResumeLayout(false);
			this->panel4->ResumeLayout(false);
			this->pn_requestRide->ResumeLayout(false);
			this->pn_requestRide->PerformLayout();
			this->pn_captains_around->ResumeLayout(false);
			this->pn_captains_around->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->refresh_anim))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox18))->EndInit();
			this->pn_scheduleRide->ResumeLayout(false);
			this->pn_scheduleRide->PerformLayout();
			this->pn_viewHistory->ResumeLayout(false);
			this->pn_viewHistory->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox19))->EndInit();
			this->pn_rate_captain->ResumeLayout(false);
			this->pn_rate_captain->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox30))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox31))->EndInit();
			this->pn_penddingList->ResumeLayout(false);
			this->pn_penddingList->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox20))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox17))->EndInit();
			this->pn_rider_schedule_list->ResumeLayout(false);
			this->pn_rider_schedule_list->PerformLayout();
			this->pn_rider_profile->ResumeLayout(false);
			this->pn_rider_profile->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox32))->EndInit();
			this->fpn_rider_status->ResumeLayout(false);
			this->status_panel->ResumeLayout(false);
			this->status_panel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox29))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox27))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox28))->EndInit();
			this->pn_riderInfo->ResumeLayout(false);
			this->panel5->ResumeLayout(false);
			this->panel5->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox16))->EndInit();
			this->pn_captainMenu->ResumeLayout(false);
			this->pn_search_riders->ResumeLayout(false);
			this->pn_search_riders->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->search_anim))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox36))->EndInit();
			this->pn_carInfo->ResumeLayout(false);
			this->pn_carInfo->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox35))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->EndInit();
			this->pn_schedule_requests->ResumeLayout(false);
			this->pn_schedule_requests->PerformLayout();
			this->pn_profile->ResumeLayout(false);
			this->pn_profile->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox26))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->EndInit();
			this->pn_status->ResumeLayout(false);
			this->flowLayoutPanel16->ResumeLayout(false);
			this->rider_status_panel->ResumeLayout(false);
			this->rider_status_panel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox15))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox33))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox34))->EndInit();
			this->pn_menu_list->ResumeLayout(false);
			this->panel6->ResumeLayout(false);
			this->panel6->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox14))->EndInit();
			this->pn_login_screan->ResumeLayout(false);
			this->pn_login->ResumeLayout(false);
			this->pn_login->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox25))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox24))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox23))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			this->pn_back->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox22))->EndInit();
			this->pn_riderRe->ResumeLayout(false);
			this->pn_riderRe->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->loading_gifr))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->EndInit();
			this->pn_captinRe->ResumeLayout(false);
			this->pn_captinRe->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->loading_gifc))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->EndInit();
			this->pn_terms->ResumeLayout(false);
			this->pn_terms->PerformLayout();
			this->pn_terms2->ResumeLayout(false);
			this->pn_terms2->PerformLayout();
			this->pn_Register->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			this->pn_start->ResumeLayout(false);
			this->pn_GIF->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->pn_GIF2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->pn_bar->ResumeLayout(false);
			this->pn_bar->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox21))->EndInit();
			this->ResumeLayout(false);

		}



#pragma endregion


		
		









		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		void Display_captain_Schedule_requests()
		{
			ifstream data_file("data.txt");
			// display history

			string data_line;
			string arr[12];
			int ind = 0;


			while (getline(data_file, data_line)) // read every line in history file
			{

				if (data_line[0] == 'S' && data_line[1] == 'R') // get all histroy rides
				{
					string s{};
					for (int i = 0; i < data_line.size(); i++)
					{
						if (data_line[i] == '#')
						{
							arr[ind++] = s;
							cout << "-) " << s << endl;
							s = {};

						}
						else
						{
							s.push_back(data_line[i]);
						}

					}
					ind = 0;

					cout << arr[1] << endl;            // flag

					if (Program_user.user_data.SUser_name == arr[1])
					{

						Ride ride;
						ride.captain.user_data.SUser_name = arr[1];
						ride.captain.user_data.full_name.firstname = arr[2];
						ride.captain.user_data.full_name.lastname = arr[3];
						ride.rider.user_data.SUser_name = arr[4];
						ride.rider.user_data.full_name.firstname = arr[5];
						ride.rider.user_data.full_name.lastname = arr[6];
						ride.Location = arr[7];
						ride.Distination = arr[8];
						ride.Sum_time = arr[9];		
						ride.Verdict = "Pending";
						ride.captain.user_data.SID = Program_user.user_data.SID;


						cout << ride.rider.user_data.full_name.firstname << endl << ride.rider.user_data.full_name.lastname << endl; // flag
						cout << ">> " << ride.Location << endl << ride.Distination << endl;







						Panel^ newPanel = gcnew Panel();
						newPanel->Size = System::Drawing::Size(560, 130);
						newPanel->Name = "panel_sch";
						newPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(18)), static_cast<System::Int32>(static_cast<System::Byte>(78)),
							static_cast<System::Int32>(static_cast<System::Byte>(80)));


						/*

			this->label100->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);



						*/


						// adding captain name label
						Label^ c_name_l = gcnew Label();
						c_name_l->AutoSize = true;
						c_name_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
						c_name_l->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							static_cast<System::Byte>(0)));
						c_name_l->Location = System::Drawing::Point(10, 10);
						c_name_l->Name = L"label20";
						c_name_l->Size = System::Drawing::Size(166, 20);
						c_name_l->TabIndex = 4;
						c_name_l->Text = L"Captain Name:";
						newPanel->Controls->Add(c_name_l); // add the label to the panel


						// adding captain name
						Label^ c_name = gcnew Label();
						c_name->AutoSize = true;
						c_name->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
						c_name->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							static_cast<System::Byte>(0)));
						c_name->Location = System::Drawing::Point(170, 10);
						c_name->Name = L"captain_name";
						c_name->Size = System::Drawing::Size(166, 20);
						c_name->TabIndex = 4;
						c_name->Text = gcnew String((ride.captain.user_data.full_name.firstname + " " + ride.captain.user_data.full_name.lastname).c_str()); //
						newPanel->Controls->Add(c_name); // add the label to the panel




						//adding location label
						Label^ location_l = gcnew Label();
						location_l->AutoSize = true;
						location_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
						location_l->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							static_cast<System::Byte>(0)));
						location_l->Location = System::Drawing::Point(10, 40);
						location_l->Name = L"label21";
						location_l->Size = System::Drawing::Size(166, 20);
						location_l->TabIndex = 4;
						location_l->Text = gcnew String("Location:"); //
						newPanel->Controls->Add(location_l); // add the label to the panel


						// adding location
						Label^ location = gcnew Label();
						location->AutoSize = true;
						location->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
						location->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							static_cast<System::Byte>(0)));
						location->Location = System::Drawing::Point(170, 40);
						location->Name = L"ride_location";
						location->Size = System::Drawing::Size(150, 30);
						location->TabIndex = 4;
						location->Text = gcnew String(ride.Location.c_str()); //
						newPanel->Controls->Add(location); // add the label to the panel




						// adding distination label
						Label^ dsitination_l = gcnew Label();
						dsitination_l->AutoSize = true;
						dsitination_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
						dsitination_l->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							static_cast<System::Byte>(0)));
						dsitination_l->Location = System::Drawing::Point(10, 70);
						dsitination_l->Name = L"label21";
						dsitination_l->Size = System::Drawing::Size(150, 30);
						dsitination_l->TabIndex = 4;
						dsitination_l->Text = gcnew String("Distination:"); //
						newPanel->Controls->Add(dsitination_l); // add the label to the panel


						// adding distination 
						Label^ distination = gcnew Label();
						distination->AutoSize = true;
						distination->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
						distination->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							static_cast<System::Byte>(0)));
						distination->Location = System::Drawing::Point(170, 70);
						distination->Name = L"ride_distination";
						distination->Size = System::Drawing::Size(150, 30);
						distination->TabIndex = 4;
						distination->Text = gcnew String(ride.Distination.c_str()); //
						newPanel->Controls->Add(distination); // add the label to the panel




						// adding captain username label
						Label^ username_l = gcnew Label();
						username_l->AutoSize = true;
						username_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
						username_l->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							static_cast<System::Byte>(0)));
						username_l->Location = System::Drawing::Point(10, 100);
						username_l->Name = L"label20";
						username_l->Size = System::Drawing::Size(166, 20);
						username_l->TabIndex = 4;
						username_l->Text = L"Captain username:";
						newPanel->Controls->Add(username_l); // add the label to the panel



						// adding captain username
						Label^ username = gcnew Label();
						username->AutoSize = true;
						username->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
						username->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							static_cast<System::Byte>(0)));
						username->Location = System::Drawing::Point(170, 100);
						username->Name = L"captain_username";
						username->Size = System::Drawing::Size(166, 20);
						username->TabIndex = 4;
						username->Text = gcnew String(ride.captain.user_data.SUser_name.c_str()); //
						newPanel->Controls->Add(username); // add the label to the panel






						//adding time label 
						Label^ time_l = gcnew Label();
						time_l->AutoSize = true;
						time_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
						time_l->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							static_cast<System::Byte>(0)));
						time_l->Location = System::Drawing::Point(360, 74);
						time_l->Name = L"label21";
						time_l->Size = System::Drawing::Size(150, 30);
						time_l->TabIndex = 4;
						time_l->Text = "Time:"; //
						newPanel->Controls->Add(time_l); // add the label to the panel







						


						//adding time 
						Label^ time = gcnew Label();
						time->AutoSize = true;
						time->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
						time->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							static_cast<System::Byte>(0)));
						time->Location = System::Drawing::Point(403, 74);
						time->Name = L"timeLabel";
						time->Size = System::Drawing::Size(150, 30);
						time->TabIndex = 4;
						time->Text = gcnew String(ride.Sum_time.c_str()); //
						newPanel->Controls->Add(time); // add the label to the panel


						check_schedule_timer->Start();
						msclr::interop::marshal_context context;
						fpn_schedule_requests->Controls->Add(newPanel);






					}


				}
			}
			data_file.close();
		}

		bool Check_plate_number(string plate)
		{
			if (plate.size() != 6)
				return 0;

			for (int i = 0; i < 6; i++)
			{
				if (i < 3 && !(plate[i] <= '9' && plate[i] >= '0'))
					return 0;

				if (i >= 3 && !(plate[i] <= 'Z' && plate[i] >= 'A'))
					return 0;

			}
			cout << ">> right plate number :)" << endl;
			return 1;

		}

		void Edit_car_info(string plate, string type, string color, string level)
		{
			//in program part
			//[1] struct
			cout << ">>>>>>RE>>>> level " << level << endl;
			Program_user.car.ILevel = {};
			Program_user.car.ILevel += level[level.size() - 1];
			Program_user.car.SColor = color;
			Program_user.car.SNumber = plate;
			Program_user.car.SType = type;

			//[2] gui
			label43->Text = gcnew String(type.c_str());
			label44->Text = gcnew String(color.c_str());
			label45->Text = gcnew String(plate.c_str());
			label46->Text = gcnew String(level.c_str());

			label32->Text = gcnew String(("Type: " + type).c_str());
			label33->Text = gcnew String(("Color: " + color).c_str());
			label34->Text = gcnew String(("Car Number: " + plate).c_str());
			label35->Text = gcnew String(("Level: " + level).c_str());
			cout << ">> GUI info edited :)" << endl;





			//files part
			// 
			// editing data in file

			ifstream data_file("account_info.txt");
			string file_lines[101];
			int cnt = 0;

			string line;
			while (getline(data_file, line))
			{
				string arr[20];
				string s{};
				int arr_ind = 0;
				for (int i = 0; i < line.size(); i++)
				{
					if (line[i] == '#')
					{
						arr[arr_ind++] = s;
						s = {};

					}
					else
					{
						s.push_back(line[i]);
					}

				}

				if (arr[0] != Program_user.user_data.SUser_name)
				{
					file_lines[cnt++] = line;
				}


			}
			data_file.close();
			ofstream output("account_info.txt");

			// other data

			//output << Riders_count << "R&" << Captains_count << "C" << endl; //counts
			for (int i = 0; i <(cnt); i++)
			{
				output << file_lines[i] << endl;
			}
			

			// re enter the edited data line
			output << Program_user.user_data.SUser_name << "#" << Program_user.user_data.SPassword << "#"
				<< Program_user.role << "#" << Program_user.user_data.SID << "#" << Program_user.user_data.full_name.firstname << "#"
				<< Program_user.user_data.full_name.lastname << "#" << Program_user.user_data.SCity_location << "#"
				<< Program_user.car.SColor << "#" << Program_user.car.ILevel << "#" << Program_user.car.SNumber << "#"
				<< Program_user.car.SType << "#" << std::fixed << std::setprecision(1) << Program_user.rating << "#" << endl; // bug here need to be fixed :)


			output.close();
			cout << ">> file data updeted :D" << endl;
			


		}


		int status_count;






		/*
		* Check_firstname(firstname, &error) &&
		Check_lastname(lastname, &error) &&
		Check_username(username, &error) &&
		Check_password(password, &error) &&
		Check_id(id, &error) &&
		*/

		/////////////////////////////////////////////////////////////////////////////////////////////////
		//captain registeration
		bool Check_username(string username, string* error)
		{
			if (username.size() == 0)
			{
				*error = "empty";
				return 0;
			}

			size_t size2 = username.size();
			for (int count = 0; count < size2; count++)
			{
				if (username[0] >= '0' && username[0] <= '9')
				{
					cout << "Invalid Username !! , Please ReEnter a Valid Username Again Without spaces and Without a number at the beginning :(" << endl;;
					*error = "begin_num";
					return 0;
				}
				else if (!((username[count] >= 'a' && username[count] <= 'z') || (username[count] >= 'A' && username[count] <= 'Z') || (username[count] >= '0' && username[count] <= '9') || username[count] == '_'))
				{
					cout << "Invalid Username !! , Please ReEnter a Valid Username Again :(" << endl;;
					*error = "special_char";
					return 0;

				}

				// Same Username  //     
				string data_line;
				ifstream accounts("accounts.txt");
				while (getline(accounts, data_line))
				{


					if (username == data_line.substr(0, data_line.find(","))) // if the username exists?
					{

						cout << " This Username is already Exists !!, Please ReEnter a Valid Username Again :D" << endl;;
						*error = "alredy_exists";
						return 0;

					}
				}

			}
			return 1;


		}
		bool Check_firstname(string firstname, string* error)
		{
			if (firstname.size() == 0)
			{
				*error = "empty";
				return 0;
			}

			for (auto i : firstname)
			{
				if (isdigit(i) || ispunct(i) || i == ' ')
				{

					cout << "Enter your correct name please\tNote: FullName can't include numbers and symbols!" << endl;;
					*error = "special_char";
					return 0;
				}

			}
			return 1;


		}
		bool Check_lastname(string lastname, string* error)
		{
			if (lastname.size() == 0)
			{
				*error = "empty";
				return 0;
			}

			for (auto i : lastname)
			{
				if (isdigit(i) || ispunct(i) || i == ' ')
				{

					cout << "Enter your correct name please\tNote: Name can't include numbers and symbols!" << endl;;
					*error = "special_char";
					return 0;
				}

			}
			return 1;

		}
		bool Check_password(string password, string* error)
		{
			size_t size3 = password.size();

			if (password.size() == 0)
			{
				*error = "empty";
				return 0;
			}

			if (size3 < 8)
			{
				cout << "Password shouldn't be less than 8 items :(" << endl;
				*error = "less_th_8";
				return 0;

			}


			for (int count = 0; count < size3; count++)
			{
				if (password[count] == ' ')
				{
					cout << "Invalid Passward !!, have spaces :(" << endl;
					*error = "have_spaces";
					return 0;

				}
			}



			return 1;
		}
		bool Check_id(string id, string* error)
		{
			if (id.size() == 0)
			{
				*error = "empty";
				return 0;
			}

			if (id.size() != 14)
			{
				cout << "User ID Must be 14 Number, Please ReEnter Your ID : " << endl;;
				*error = "less_th_14";
				return 0;
			}

			for (int count = 0; count < 14; count++)
			{

				if (!(id[count] >= '0' && id[count] <= '9') || id[count] == ' ')
				{
					cout << "User ID Must Have Only Digits :(" << endl;
					*error = "special_char";
					return 0;

				}

			}


			return 1;
		}
		bool Check_captain_location(string location, string* error)
		{

			if (location.empty())
			{
				cout << "Empty location" << endl;
				*error = "empty";
				return 0;
			}



			return 1;
		}
		bool Check_captain_plate(string plate, string* error) /////////
		{
			if (plate.empty())
			{
				cout << "Empty plate number :( " << endl;
				*error = "empty";
				return 0;
			}

			if (plate.size() != 6)
			{
				cout << "Car Number Have 3 Digits and 3 Characters! :D" << endl;
				*error = "not_6";
				return 0;
			}

			for (int count = 0; count < 6; count++)
			{
				if (count < 3 && !(plate[count] >= '0' && plate[count] <= '9'))
				{
					cout << "Invalid Plate Number, Try again :D " << endl;
					*error = "sorting";
					return 0;
				}

				if (count >= 3 && !(plate[count] >= 'A' && plate[count] <= 'Z'))
				{
					cout << "Invalid Plate Number, Try again :D " << endl;
					*error = "sorting";
					return 0;
				}

			}


			return 1;
		}
		bool Check_captain_level(string level, string* error)
		{
			if (level.empty())
			{
				cout << "Empty car level :( " << endl;
				*error = "empty";
				return 0;
			}

			return 1;
		}
		bool Check_captain_color(string color, string* error)
		{
			if (color.empty())
			{
				cout << "Empty car color :( " << endl;
				*error = "empty";
				return 0;
			}

			return 1;
		}
		bool Check_captain_type(string type, string* error)
		{
			if (type.empty())
			{
				cout << "Empty car type :( " << endl;
				*error = "empty";
				return 0;
			}

			return 1;
		}

		// update
		void Update_counts(string count)
		{
			ifstream data_file("account_info.txt");
			string file_lines[51];
			int cnt = 0;

			string line;
			while (getline(data_file, line))
			{


				if (line.find('#') != string::npos)
				{
					file_lines[cnt++] = line;
				}


			}

			data_file.close();

			ofstream output("account_info.txt");

			// re enter the edited data line (count)
			output << count << endl;

			// other data
			for (int i = 0; i <(cnt); i++)
			{
				output << file_lines[i] << endl;
			}
			output.close();
			cout << ">> new counts updated :D to " << count << endl;

		}



		void Change_counts(string new_count)
		{
			//////////////////////////////////////////////////////////////
			// 
			// 
			// ifstream data_file("account_info.txt");

			ifstream data_file("account_info.txt");
			string file_lines[50]; // to collect all lines from the file eccept the nR&mC
			int cnt = 0;

			string line;
			while (getline(data_file, line))
			{


				if (line.find('#') != string::npos)
				{
					file_lines[cnt++] = line;
				}



			}
			data_file.close();

			ofstream output_data("account_info.txt");
			output_data << Riders_count << "R&" << Captains_count << "C" << endl; // output new counts

			// other data output
			for (int i = 0; i < (cnt); i++)
			{
				output_data << file_lines[i] << endl;
			}

			cout << "flag E" << endl;
			cout << "**New captains and riders count updated**" << endl;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 
		// captain register


		void Register_user(string firstname, string lastname, string username, string password, string id, string car_number, string car_level, string car_color, string car_type, string location)
		{
			/////increment user count


			Captains_count++;
			string new_count = std::to_string(Riders_count) + "R&" + std::to_string(Captains_count) + 'C';
			Change_counts(new_count);


			/////////////////////////////////////////////////////////////////////////////
			// account data file
			ofstream output_data("account_info.txt",std::ios::app);
			output_data << username << "#" << password << "#"
				<< "C" << "#" << id << "#" << firstname << "#"
				<< lastname << "#" << location << "#"
				<< car_color << "#" << car_level.back() << "#" << car_number << "#"
				<< car_type << "#" << "5.0" << "#" << endl;



			//accounts file
			ofstream output_account("accounts.txt", std::ios::app);
			output_account << username << ',' << password << endl;
			output_account.close();


			cout << ">> registeration output to files completed :D (captain)" << endl;


		}


		// rider registeration
		void Register_user( string firstname, string lastname, string username, string password, string id)
		{

			Riders_count++;
			string new_count = std::to_string(Riders_count) + "R&" + std::to_string(Captains_count) + 'C';
			Change_counts(new_count);

			///////////////////////////////////////////////////////////////////////////////////////


			ofstream output_data("account_info.txt",std::ios::app); // appending (to not delete the last data)
			output_data << username << "#" << password << "#"
				<< "R" << "#" << id << "#" << firstname << "#"
				<< lastname << '#' << endl;



			//accounts file
			ofstream output_account("accounts.txt", std::ios::app);
			output_account << username << ',' << password << endl;
			output_account.close();

			cout << ">> registeration output to files completed :D (rider)" << endl;


		}

		void Clear_captain_register_boxes()
		{
			textBox13->Text = "";
			textBox12->Text = "";
			textBox11->Text = "";
			textBox10->Text = "";
			textBox9->Text = "";
			textBox14->Text = "";
			checkBox2->Checked = 0;

			comboBox11->SelectedIndex = -1;
			comboBox1->SelectedIndex = -1;
			comboBox2->SelectedIndex = -1;
			comboBox12->SelectedIndex = -1;

		}

		void Clear_rider_register_boxes()
		{
			textBox4->Text = "";
			textBox5->Text = "";
			textBox6->Text = "";
			textBox7->Text = "";
			textBox8->Text = "";
			checkBox1->Checked = 0;


		}

		Rider convert_user_to_rider(string level, string location, string distination)
		{
			Rider rider;
			rider.desired_car_level = level;
			rider.Distination = distination;
			rider.user_data.full_name.firstname = Program_user.user_data.full_name.firstname;
			rider.user_data.full_name.lastname = Program_user.user_data.full_name.lastname;
			rider.user_data.SCity_location = Program_user.user_data.SCity_location;
			rider.user_data.SID = Program_user.user_data.SID;
			rider.user_data.SPassword = Program_user.user_data.SPassword;
			rider.user_data.SUser_name = Program_user.user_data.SUser_name;

			return rider;
		}


		void set_pending_ride(string level, string location, string distination)
		{
			Rider ride_rider = convert_user_to_rider(level, location, distination);
			//Captain ride_captain = Get_random_captain(location);

			Ride ride;
			//ride.captain = ride_captain;
			ride.rider = ride_rider;
			ride.accepted = 0;
			ride.Car_level = level;
			ride.Distination = distination;
			ride.Location = location;
			ride.Verdict = "pending";

			msclr::interop::marshal_context context;
			ride.Sum_time = context.marshal_as<std::string>(rider_clock->Text);


			Pending_ride = ride;
			////
		}


		void set_status_message(string message)
		{
			status_message->Text = gcnew String((message).c_str());

			status_panel->Visible = 1;

			pictureBox27->Visible = 1; //exit

			pictureBox29->Visible = 1;//notification


		}

		void clear_rider_status_message()
		{
			status_message->Text = "You have no notifications";
			status_panel->Visible = 1;
			pictureBox27->Visible = 0; //exit
			pictureBox29->Visible = 0;//notification


		}


		/*
		start next time here by adding timer for the ride beginning
		*/

		void OnButton_cancel_Click(Object^ sender, EventArgs^ e)
		{
			// Get the button control that triggered the event
			Button^ button = dynamic_cast<Button^>(sender);
			// Get the parent control of the button (which should be a panel)
			Panel^ panel = dynamic_cast<Panel^>(button->Parent);
			if (panel != nullptr) {

				if (MessageBox::Show("Are you sure you want cancel this ride", "Cancel a ride", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
				{
					Console::WriteLine(panel->Name);
					fpn_pendingList->Controls->Remove(panel);
					set_status_message("You canceled this pending ride");
					in_a_Ride = 0;

				}
			}
			else
			{
				cout << "null pending panel error" << endl;
			}

		}


		//////////////////////////////////rider funcs
		void Add_to_rider_pending_list(Ride ride)
		{

			// adding to gui list
			msclr::interop::marshal_context context;

			Panel^ newPanel = gcnew Panel();
			newPanel->Size = System::Drawing::Size(550, 130);
			newPanel->BackColor = System::Drawing::Color::Teal;
			newPanel->Location = System::Drawing::Point(5, 5);
			newPanel->Name = L"pn_pending_ride";
			newPanel->TabIndex = 0;


			/*






			this->
			this->label52->Name = L"label52";
			this->label52->Size = System::Drawing::Size(109, 17);
			this->label52->TabIndex = 1;
			this->label52->Text = L"captain_name";
			*/


			// adding captain name label
			Label^ c_name_l = gcnew Label();
			c_name_l->AutoSize = true;
			c_name_l->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			c_name_l->BackColor = System::Drawing::Color::Teal;
			c_name_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			c_name_l->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			c_name_l->Location = System::Drawing::Point(10, 10);
			c_name_l->Name = L"label20";
			c_name_l->Size = System::Drawing::Size(68, 17);
			c_name_l->TabIndex = 1;
			c_name_l->Text = L"Captain:";
			newPanel->Controls->Add(c_name_l); // add the label to the panel


			// adding captain name
			Label^ c_name = gcnew Label();
			c_name->BackColor = System::Drawing::Color::Teal;
			c_name->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			c_name->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			c_name->AutoSize = true;
			c_name->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			c_name->Location = System::Drawing::Point(140, 10);
			c_name->Name = L"captain_name";
			c_name->Size = System::Drawing::Size(68, 17);
			c_name->TabIndex = 1;
			c_name->Text = gcnew String((ride.captain.user_data.full_name.firstname + " " + ride.captain.user_data.full_name.lastname).c_str()); //
			newPanel->Controls->Add(c_name); // add the label to the panel


			// adding level label
			Label^ v_l = gcnew Label();
			v_l->BackColor = System::Drawing::Color::Teal;
			v_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			v_l->AutoSize = true;
			v_l->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			v_l->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			v_l->Location = System::Drawing::Point(10, 40);
			v_l->Name = L"label21";
			v_l->Size = System::Drawing::Size(68, 17);
			v_l->TabIndex = 1;
			v_l->Text = gcnew String("Car level:"); //
			newPanel->Controls->Add(v_l); // add the label to the panel


			// level
			Label^ level = gcnew Label();
			level->BackColor = System::Drawing::Color::Teal;
			level->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			level->AutoSize = true;
			level->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			level->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			level->Location = System::Drawing::Point(140, 40);
			level->Name = L"car_level";
			level->Size = System::Drawing::Size(68, 17);
			level->TabIndex = 1;
			level->Text = gcnew String(ride.Car_level.c_str()); //
			newPanel->Controls->Add(level); // add the label to the panel



			//adding location label
			Label^ location_l = gcnew Label();
			location_l->BackColor = System::Drawing::Color::Teal;
			location_l->AutoSize = true;
			location_l->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			location_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			location_l->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			location_l->Location = System::Drawing::Point(10, 70);
			location_l->Name = L"label21";
			location_l->Size = System::Drawing::Size(68, 17);
			location_l->TabIndex = 1;
			location_l->Text = gcnew String("Location:"); //
			newPanel->Controls->Add(location_l); // add the label to the panel



			// adding location
			Label^ location = gcnew Label();
			location->BackColor = System::Drawing::Color::Teal;
			location->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			location->AutoSize = true;
			location->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			location->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			location->Location = System::Drawing::Point(140, 70);
			location->Name = L"captain_location";
			location->Size = System::Drawing::Size(68, 17);
			location->TabIndex = 1;
			location->Text = gcnew String(ride.Location.c_str()); //
			newPanel->Controls->Add(location); // add the label to the panel



			//adding distination label
			Label^ distination_l = gcnew Label();
			distination_l->BackColor = System::Drawing::Color::Teal;
			distination_l->AutoSize = true;
			distination_l->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			distination_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			distination_l->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			distination_l->Location = System::Drawing::Point(10, 100);
			distination_l->Name = L"label21";
			distination_l->Size = System::Drawing::Size(68, 17);
			distination_l->TabIndex = 1;
			distination_l->Text = gcnew String("Distination:"); //
			newPanel->Controls->Add(distination_l); // add the label to the panel



			// adding distination
			Label^ distination = gcnew Label();
			distination->BackColor = System::Drawing::Color::Teal;
			distination->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			distination->AutoSize = true;
			distination->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			distination->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			distination->Location = System::Drawing::Point(140, 100);
			distination->Name = L"captain_distination";
			distination->Size = System::Drawing::Size(68, 17);
			distination->TabIndex = 1;
			distination->Text = gcnew String(ride.Distination.c_str()); //
			newPanel->Controls->Add(distination); // add the label to the panel






			//adding cancel button
			Button^ cancel_btn = gcnew Button;
			cancel_btn->BackColor = System::Drawing::Color::IndianRed;
			cancel_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			cancel_btn->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)));
			cancel_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			cancel_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			cancel_btn->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			cancel_btn->Location = System::Drawing::Point(450, 5);
			cancel_btn->Name = L"button_cancel";
			cancel_btn->Size = System::Drawing::Size(77, 23);
			cancel_btn->TabIndex = 2;
			cancel_btn->Text = L"Cancel";
			cancel_btn->UseVisualStyleBackColor = false;
			cancel_btn->Click += gcnew EventHandler(this, &MyForm::OnButton_cancel_Click);
			newPanel->Controls->Add(cancel_btn);

			fpn_pendingList->Controls->Add(newPanel);








		}

		/*Captain Get_random_captain(string location)
		{

			srand(time(0));

			string rider_loc = '#' + location + '#';
			cout << "loking for captains around : " << rider_loc << endl;

			ifstream data_file("account_info.txt");
			string data_line;
			int random_captain_ind = rand() % Captains_count;
			int current_ind = 0;

			string arr[12];
			int ind = 0;
			while (getline(data_file, data_line))
			{
				if (data_line.find("#C#") != string::npos && data_line.find(rider_loc) != string::npos)
				{
					if (current_ind == random_captain_ind)
					{
						cout << "random captain found !" << endl;

						string s{};
						for (int i = 0; i < data_line.size(); i++)
						{
							if (data_line[i] == '#')
							{
								arr[ind++] = s;
								s = {};

							}
							else
							{
								s.push_back(data_line[i]);
							}

						}

						break;
					}
					else
					{
						current_ind++;
					}
				}

			}
			cout << "end of Get_random_captain" << endl;

			kareem100#19196789#C#23560907900067#kareem#adel#South Sinai#Orange#2#765FSF#BMW#


			Captain captain;
			captain.user_data.SUser_name = arr[0];
			captain.user_data.SPassword = arr[1];
			captain.user_data.SID = arr[3];
			captain.user_data.full_name.firstname = arr[4];
			captain.user_data.full_name.lastname = arr[5];
			captain.user_data.SCity_location = arr[6];
			captain.car_info.SColor = arr[7];
			captain.car_info.ILevel = arr[8];
			captain.car_info.SNumber = arr[9];
			captain.car_info.SType = arr[10];
			return captain;

		}*/

		////show captain around////////////////////////////////////////////////////////////////////

		void Add_to_rider_schedule_list(Ride ride, string hours, string minutes, string ampm)
		{
			//GUI
		;

			// pushing the ride as a panel inside the flow panel


			Panel^ newPanel = gcnew Panel();
			newPanel->Size = System::Drawing::Size(560, 130);
			newPanel->Name = "panel_sch";
			newPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(18)), static_cast<System::Int32>(static_cast<System::Byte>(78)),
				static_cast<System::Int32>(static_cast<System::Byte>(80)));


			/*

this->label100->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);



			*/


			// adding captain name label
			Label^ c_name_l = gcnew Label();
			c_name_l->AutoSize = true;
			c_name_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			c_name_l->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			c_name_l->Location = System::Drawing::Point(10, 10);
			c_name_l->Name = L"label20";
			c_name_l->Size = System::Drawing::Size(166, 20);
			c_name_l->TabIndex = 4;
			c_name_l->Text = L"Captain Name:";
			newPanel->Controls->Add(c_name_l); // add the label to the panel


			// adding captain name
			Label^ c_name = gcnew Label();
			c_name->AutoSize = true;
			c_name->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			c_name->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			c_name->Location = System::Drawing::Point(170, 10);
			c_name->Name = L"captain_name";
			c_name->Size = System::Drawing::Size(166, 20);
			c_name->TabIndex = 4;
			c_name->Text = gcnew String((ride.captain.user_data.full_name.firstname + " " + ride.captain.user_data.full_name.lastname).c_str()); //
			newPanel->Controls->Add(c_name); // add the label to the panel




			//adding location label
			Label^ location_l = gcnew Label();
			location_l->AutoSize = true;
			location_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			location_l->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			location_l->Location = System::Drawing::Point(10, 40);
			location_l->Name = L"label21";
			location_l->Size = System::Drawing::Size(166, 20);
			location_l->TabIndex = 4;
			location_l->Text = gcnew String("Location:"); //
			newPanel->Controls->Add(location_l); // add the label to the panel


			// adding location
			Label^ location = gcnew Label();
			location->AutoSize = true;
			location->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			location->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			location->Location = System::Drawing::Point(170, 40);
			location->Name = L"ride_location";
			location->Size = System::Drawing::Size(150, 30);
			location->TabIndex = 4;
			location->Text = gcnew String(ride.Location.c_str()); //
			newPanel->Controls->Add(location); // add the label to the panel




			// adding distination label
			Label^ ditination_l = gcnew Label();
			ditination_l->AutoSize = true;
			ditination_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			ditination_l->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			ditination_l->Location = System::Drawing::Point(10, 70);
			ditination_l->Name = L"label21";
			ditination_l->Size = System::Drawing::Size(150, 30);
			ditination_l->TabIndex = 4;
			ditination_l->Text = gcnew String("Distination:"); //
			newPanel->Controls->Add(ditination_l); // add the label to the panel


			// adding distination 
			Label^ ditination = gcnew Label();
			ditination->AutoSize = true;
			ditination->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			ditination->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			ditination->Location = System::Drawing::Point(170, 70);
			ditination->Name = L"ride_distination";
			ditination->Size = System::Drawing::Size(150, 30);
			ditination->TabIndex = 4;
			ditination->Text = gcnew String(ride.Distination.c_str()); //
			newPanel->Controls->Add(ditination); // add the label to the panel

		


			// adding captain username label
			Label^ username_l = gcnew Label();
			username_l->AutoSize = true;
			username_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			username_l->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			username_l->Location = System::Drawing::Point(10, 100);
			username_l->Name = L"label20";
			username_l->Size = System::Drawing::Size(166, 20);
			username_l->TabIndex = 4;
			username_l->Text = L"Captain username:";
			newPanel->Controls->Add(username_l); // add the label to the panel

			// adding captain username
			Label^ username = gcnew Label();
			username->AutoSize = true;
			username->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			username->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			username->Location = System::Drawing::Point(170, 100);
			username->Name = L"captain_username";
			username->Size = System::Drawing::Size(166, 20);
			username->TabIndex = 4;
			username->Text = gcnew String(ride.captain.user_data.SUser_name.c_str()); //
			newPanel->Controls->Add(username); // add the label to the panel






			//adding time label 
			Label^ time_l = gcnew Label();
			time_l->AutoSize = true;
			time_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			time_l->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			time_l->Location = System::Drawing::Point(313, 74);
			time_l->Name = L"label21";
			time_l->Size = System::Drawing::Size(150, 30);
			time_l->TabIndex = 4;
			time_l->Text = "Time:"; //
			newPanel->Controls->Add(time_l); // add the label to the panel







			int h = System::Convert::ToInt16(gcnew String(hours.c_str()));
			int m = System::Convert::ToInt16(gcnew String(minutes.c_str()));
			string ride_time;

			if (m >= 10 && h >= 10)
				ride_time = hours + ':' + minutes + ':' + ampm;
			else if(m < 10 && h < 10)
				ride_time = '0' + hours + ':' + '0' + minutes + ':' + ampm;
			else if (m >= 10)
				ride_time = '0' + hours + ':' + minutes + ':' + ampm;
			else if (h >= 10)
				ride_time = hours + ':' + '0' + minutes + ':' + ampm;
			else
				cout << "time error in Add_to_rider_schedule_list FUNC" << endl;


			//adding time 
			Label^ time = gcnew Label();
			time->AutoSize = true;
			time->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			time->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			time->Location = System::Drawing::Point(403, 74);
			time->Name = L"timeLabel";
			time->Size = System::Drawing::Size(150, 30);
			time->TabIndex = 4;
			time->Text = gcnew String(ride_time.c_str()); //
			newPanel->Controls->Add(time); // add the label to the panel


			check_schedule_timer->Start();
			msclr::interop::marshal_context context;
			fpn_rider_schedule_list->Controls->Add(newPanel);



		}


		void OnButtonClick(Object^ sender, EventArgs^ e)
		{
			// Retrieve the button control that was clicked
			Button^ button = dynamic_cast<Button^>(sender);


			// Retrieve the label control in the same panel as the button
			Label^ label = dynamic_cast<Label^>(button->Parent->Controls["captain_name"]); //captain_username
			Label^ username = dynamic_cast<Label^>(button->Parent->Controls["captain_username"]);

			msclr::interop::marshal_context context;
			string name = context.marshal_as<std::string>(label->Text);

			
			


			// Display the label text
			if (making_schedule_ride)
			{
				string msg = "Are you sure you want to schedule a ride with captain " + name;
				if (MessageBox::Show(gcnew String(msg.c_str()), "Schedule a ride", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
				{
					// agreed to a captain

					//clearing boxes
					comboBox3->SelectedIndex = -1;
					comboBox4->SelectedIndex = -1;
					comboBox13->SelectedIndex = -1;
					req_error->Visible = 0;

					MessageBox::Show("You have scheduled your ride successfully!", gcnew String(("Captain " + name + ":").c_str()));

					label56->Visible = 0;
					fpn_captains_around->Visible = 0;
					pictureBox17->BringToFront();
					in_a_Ride = 0;

					//ride
					Pending_ride.captain.user_data.full_name.firstname = name.substr(0, name.find(' '));
					Pending_ride.captain.user_data.full_name.lastname = name.substr(name.find(' ') + 1, name.size() - 1);
					Pending_ride.captain.user_data.SUser_name = context.marshal_as<std::string>(username->Text);

					cout << "the names >> " << endl;
					cout << Pending_ride.captain.user_data.full_name.firstname << '#' << endl;
					cout << Pending_ride.captain.user_data.full_name.lastname << '#' << endl;

					Add_to_rider_schedule_list(Pending_ride,s_hours,s_minutes,s_ampm);
					//Ride_timer->Start();
					cout << "ride added to schedule list" << endl;



					status_message->Text = gcnew String(("Your ride with captain " + name + " has been added to schedule list").c_str());
					status_panel->Visible = 1;
					pictureBox27->Visible = 1; //exit
					pictureBox29->Visible = 1;//notification
					fpn_captains_around->Controls->Clear();




					/////
					int h = System::Convert::ToInt16(gcnew String(s_hours.c_str()));
					int m = System::Convert::ToInt16(gcnew String(s_minutes.c_str()));
					string ride_time;

					if (m >= 10 && h >= 10)
						ride_time = s_hours + ':' + s_minutes + ':' + s_ampm;
					else if (m < 10 && h < 10)
						ride_time = '0' + s_hours + ':' + '0' + s_minutes + ':' + s_ampm;
					else if (m >= 10)
						ride_time = '0' + s_hours + ':' + s_minutes + ':' + s_ampm;
					else if (h >= 10)
						ride_time = s_hours + ':' + '0' + s_minutes + ':' + s_ampm;
					else
						cout << "time error in ONButtonClick FUNC" << endl;

					//adding to files for the captain schedule requests

					ofstream data_file("data.txt", std::ios::app);
					data_file << "SR" << "#" << Pending_ride.captain.user_data.SUser_name << "#" << Pending_ride.captain.user_data.full_name.firstname << "#"
						<< Pending_ride.captain.user_data.full_name.lastname << "#" << Program_user.user_data.SUser_name << "#" << Program_user.user_data.full_name.firstname << "#"
						<< Program_user.user_data.full_name.lastname<< "#" << Pending_ride.Location << "#" << Pending_ride.Distination << "#" << ride_time << "#" << endl;
					

				//	cout << Pending_ride.captain.user_data.full_name.firstname << '#' << endl;
					//cout << Pending_ride.captain.user_data.full_name.lastname << '#' << endl;



				

					data_file.close();
					cout << "scheduled request added to data file :)" << endl;



				}

			}
			else
			{
				string msg = "Are you sure you want to Begin the ride with captain " + name;
				if (MessageBox::Show(gcnew String(msg.c_str()), "Requesting a ride", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
				{
					// agreed to a captain

					//clearing boxes
					comboBox3->SelectedIndex = -1;
					comboBox4->SelectedIndex = -1;
					comboBox13->SelectedIndex = -1;
					req_error->Visible = 0;




					MessageBox::Show("Your ride will begin soon", gcnew String(("Captain " + name + ":").c_str()));
					label56->Visible = 0;
					fpn_captains_around->Visible = 0;
					pictureBox19->BringToFront();
					in_a_Ride = 1;

					//ride
					Pending_ride.captain.user_data.full_name.firstname = name.substr(0, name.find(' ')); 
					Pending_ride.captain.user_data.full_name.lastname = name.substr(name.find(' ') + 1, name.size() - 1);
					Pending_ride.captain.user_data.SUser_name = context.marshal_as<std::string>(username->Text);

					Add_to_rider_pending_list(Pending_ride);
					Ride_timer->Start();
					cout << "ride added to pending list" << endl;



					status_message->Text = gcnew String(("Your ride with captain " + name + " has been added to pending list").c_str());
					status_panel->Visible = 1;
					pictureBox27->Visible = 1; //exit
					pictureBox29->Visible = 1;//notification
					fpn_captains_around->Controls->Clear();

					////////////////////////////////////////////
					

				}

			}
			
			//MessageBox::Show(label->Text);

		}

		void Set_rider_profile()
		{
			label118->Text = gcnew String(Program_user.user_data.full_name.firstname.c_str());
			cout << Program_user.user_data.full_name.firstname << endl;
			cout << "..> profile flag" << endl;
			rider_fullname->Text = gcnew String((Program_user.user_data.full_name.firstname + ' ' + Program_user.user_data.full_name.lastname).c_str());
			cout << "rider name set!" << endl;
			label117->Text = gcnew String(Program_user.user_data.full_name.lastname.c_str());
			label116->Text = gcnew String(Program_user.user_data.SID.c_str());
			label114->Text = gcnew String(Program_user.user_data.SUser_name.c_str());


		}

		void Display_on_captains_list(Captain captain)
		{

			// this will be the pushing to the panel 
			cout << "> captain : " << captain.user_data.full_name.firstname << ' ' << captain.user_data.full_name.lastname << endl;


			msclr::interop::marshal_context context;
			Panel^ newPanel = gcnew Panel();
			newPanel->Size = System::Drawing::Size(285, 115);
			newPanel->BackColor = System::Drawing::SystemColors::WindowFrame;





			// adding captain name label
			Label^ c_name_l = gcnew Label();
			c_name_l->AutoSize = true;
			c_name_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			c_name_l->BackColor = System::Drawing::SystemColors::WindowFrame;
			c_name_l->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			c_name_l->Location = System::Drawing::Point(10, 10);
			c_name_l->Name = L"label20";
			c_name_l->Size = System::Drawing::Size(68, 17);
			c_name_l->TabIndex = 3;
			c_name_l->Text = L"Captain:";
			newPanel->Controls->Add(c_name_l); // add the label to the panel

			// adding captain name
			Label^ c_name = gcnew Label();
			c_name->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			c_name->AutoSize = true;
			c_name->BackColor = System::Drawing::SystemColors::WindowFrame;
			c_name->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			c_name->Location = System::Drawing::Point(100, 10);
			c_name->Name = L"captain_name";
			c_name->Size = System::Drawing::Size(68, 17);
			c_name->TabIndex = 3;
			c_name->Text = gcnew String((captain.user_data.full_name.firstname + " " + captain.user_data.full_name.lastname).c_str()); //
			newPanel->Controls->Add(c_name); // add the label to the panel



			// adding color label
			Label^ v_c = gcnew Label();
			v_c->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			v_c->AutoSize = true;
			v_c->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			v_c->BackColor = System::Drawing::SystemColors::WindowFrame;
			v_c->Location = System::Drawing::Point(10, 40);
			v_c->Name = L"label21";
			v_c->Size = System::Drawing::Size(68, 17);
			v_c->TabIndex = 3;
			v_c->Text = gcnew String("Car color:"); //
			newPanel->Controls->Add(v_c); // add the label to the panel


			// color
			Label^ color = gcnew Label();
			color->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			color->AutoSize = true;
			color->BackColor = System::Drawing::SystemColors::WindowFrame;
			color->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			color->Location = System::Drawing::Point(100, 40);
			color->Name = L"car_color";
			color->Size = System::Drawing::Size(68, 17);
			color->TabIndex = 3;
			color->Text = gcnew String(captain.car_info.SColor.c_str()); //
			newPanel->Controls->Add(color); // add the label to the panel



			//adding location label
			Label^ location_l = gcnew Label();
			location_l->AutoSize = true;
			location_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			location_l->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			location_l->BackColor = System::Drawing::SystemColors::WindowFrame;
			location_l->Location = System::Drawing::Point(10, 70);
			location_l->Name = L"label21";
			location_l->Size = System::Drawing::Size(68, 17);
			location_l->TabIndex = 3;
			location_l->Text = gcnew String("Location:"); //
			newPanel->Controls->Add(location_l); // add the label to the panel



			// adding location
			Label^ location = gcnew Label();
			location->AutoSize = true;
			location->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			location->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			location->Location = System::Drawing::Point(100, 70);
			location->Name = L"captain_location";
			location->BackColor = System::Drawing::SystemColors::WindowFrame;
			location->Size = System::Drawing::Size(68, 17);
			location->TabIndex = 3;
			location->Text = gcnew String(captain.user_data.SCity_location.c_str()); //
			newPanel->Controls->Add(location); // add the label to the panel

			// hiddden username
			Label^ username = gcnew Label();
			username->AutoSize = true;
			username->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			username->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			username->Location = System::Drawing::Point(120, 70);
			username->Name = L"captain_username";
			username->BackColor = System::Drawing::SystemColors::WindowFrame;
			username->Size = System::Drawing::Size(68, 17);
			username->TabIndex = 3;
			username->Visible = 0;
			username->Text = gcnew String(captain.user_data.SUser_name.c_str()); //
			newPanel->Controls->Add(username); // add the label to the panel



			//adding choose button
			Button^ choose = gcnew Button;
			choose->BackColor = System::Drawing::SystemColors::ScrollBar;
			choose->FlatAppearance->BorderColor = System::Drawing::Color::White;
			choose->Cursor = System::Windows::Forms::Cursors::Hand;
			choose->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightGreen;
			choose->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			choose->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			choose->Location = System::Drawing::Point(214, 86);
			choose->Name = L"choose_by_me";
			choose->Size = System::Drawing::Size(66, 26);
			choose->TabIndex = 19;
			choose->Text = L"Choose";
			choose->UseVisualStyleBackColor = false;

			choose->Click += gcnew EventHandler(this, &MyForm::OnButtonClick);

			newPanel->Controls->Add(choose);



			/*


			*/




			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// 
			// adding to flow layout panel
			fpn_captains_around->Controls->Add(newPanel);

			cout << "end of display captain" << endl;

		}


		void Search_captains_around(string location)
		{

			system("cls");
			srand(time(0));

		
			// note than i spent 12 hour writing this logic, if u change it u return it (:D

			string rider_loc = '#' + location + '#';
			int random_count = rand()%(Captains_count+1); // 4 - > 2
			fpn_captains_around->Controls->Clear();
			
			cout << "*The captains Around your Location* " << location << endl;

			ifstream data_file("account_info.txt");
			string data_line;
			while (getline(data_file, data_line))
			{
				
					//random_captains_count--;
					//cout << "random captain found !" << endl;

					// translating . . .
					string s{};
					string arr[13];
					int ind = 0;
					for (int i = 0; i < data_line.size(); i++)
					{
						if (data_line[i] == '#')
						{
							arr[ind++] = s;
							s = {};

						}
						else
						{
							s.push_back(data_line[i]);
						}

					}
					cout << random_count << endl;
					//checking . . 
					cout << ">>" << arr[6] << endl;
					if (arr[2] == "C" && arr[6] == location && random_count > 0)
					{

						//collecting..


						Captain captain;
						captain.user_data.SUser_name = arr[0];
						captain.user_data.SPassword = arr[1];
						captain.user_data.SID = arr[3];
						captain.user_data.full_name.firstname = arr[4];
						captain.user_data.full_name.lastname = arr[5];
						captain.user_data.SCity_location = arr[6];
						captain.car_info.SColor = arr[7];
						captain.car_info.ILevel = arr[8];
						captain.car_info.SNumber = arr[9];
						captain.car_info.SType = arr[10];
						captain.rating = stof(arr[11]);

						Display_on_captains_list(captain);


						random_count--;
					}
					else if (random_count <= 0) break;
					

					
				
			}


			cout << "flag end around" << endl;
		}

		

		void Add_to_history(Ride ride)
		{
			

			//add to data file
			ofstream Data_file("data.txt",std::ios::app);

			cout << "WANTED FLAG: " << endl;



			Data_file << "HR" << '#' << Program_user.user_data.SUser_name << '#' << Pending_ride.captain.user_data.full_name.firstname << ' ' << Pending_ride.captain.user_data.full_name.lastname
				<< '#' << Pending_ride.Location << '#' << Pending_ride.Distination << '#' << endl;

			cout << "Ride added to history file " << endl;

			

		}

		
			


		void Change_captain_rating(float rating)
		{
			
			//files part
			// 
			// editing data in file
			cout << ">>" << "coming rating: " << rating << endl;
			cout << "flag A" << endl;

			Captain _wanted;

			ifstream data_file("account_info.txt");
			string file_lines[50];
			int cnt = 0;

			string line;
			while (getline(data_file, line))
			{
				string arr[20];
				string s{};
				int arr_ind = 0;
				for (int i = 0; i < line.size(); i++)
				{
					if (line[i] == '#')
					{
						arr[arr_ind++] = s;
						s = {};

					}
					else
					{
						s.push_back(line[i]);
					}

				}

				if (arr[0] != Pending_ride.captain.user_data.SUser_name)
				{
					file_lines[cnt++] = line;
				}
				else
				{
					cout << "flag B" << endl;
					// record data for the wanted captain
					_wanted.user_data.SUser_name = arr[0];
					cout << _wanted.user_data.SUser_name << endl;
					_wanted.user_data.SPassword = arr[1];
					//_wanted.role = arr[2];
					_wanted.user_data.SID = arr[3];
					_wanted.user_data.full_name.firstname = arr[4];
					_wanted.user_data.full_name.lastname = arr[5];
					_wanted.user_data.SCity_location = arr[6];
					cout << "flag B1" << endl;
					_wanted.car_info.SColor = arr[7];
					_wanted.car_info.ILevel = arr[8];
					_wanted.car_info.SNumber = arr[9];
					_wanted.car_info.SType = arr[10];
					cout << "flag B2" << endl;
					cout << ".." << arr[11] << endl;
					_wanted.rating = stof(arr[11]); // trans. from string 2.32 to float
					cout << "flag B3" << endl;
					float current_rating = _wanted.rating;
					float edited_rating;
					cout << "flag C" << endl;

					cout << ">>current rating for " << _wanted.user_data.full_name.firstname << ' ' << _wanted.user_data.full_name.lastname << " is " << current_rating << endl;
					if (rating == 1)
					{
						if (current_rating >= 0.8)
						{
							edited_rating = current_rating - 0.3;

						}
						else
						{
							edited_rating = 0.5;
						}

					}
					else if (rating == 2.0)
					{
						if (current_rating >= 0.8)
						{
							edited_rating = current_rating - 0.2;

						}
						else
						{
							edited_rating = 0.5;
						}

					}
					else if (rating == 3.0)
					{
						if (current_rating >= 2.5)
						{
							edited_rating = current_rating - 0.2;

						}
						else if (current_rating <= 4.8)
						{
							edited_rating = current_rating + 0.2;
						}

					}
					else if (rating == 4.0)
					{
						if (current_rating < 4.7)
						{
							edited_rating = current_rating + 0.3;

						}
						else if (current_rating <= 4.9)
						{
							edited_rating = current_rating + 0.1;
						}


					}
					else //5
					{
						if (current_rating <= 4.5)
						{
							edited_rating = current_rating + 0.5;

						}
						else if (current_rating <= 4.0)
						{
							edited_rating = current_rating + 1.0;
						}

					}
					cout << "flag D" << endl;
					_wanted.rating = edited_rating;
					cout << "new ratng: " << edited_rating << endl;
					cout << "flag E" << endl;




				}


			}
			data_file.close();


			ofstream output("account_info.txt");
			//output << Riders_count << "R&" << Captains_count << "C" << endl;

			// other data
			for (int i = 0; i < (cnt); i++)
			{
				output << file_lines[i] << endl;
			}
			cout << "flag E" << endl;

			// re enter the edited data line
			output << _wanted.user_data.SUser_name << "#" << _wanted.user_data.SPassword << "#"
				<< "C" << "#" << _wanted.user_data.SID << "#" << _wanted.user_data.full_name.firstname << "#"
				<< _wanted.user_data.full_name.lastname << "#" << _wanted.user_data.SCity_location << "#"
				<< _wanted.car_info.SColor << "#" << _wanted.car_info.ILevel << "#" << _wanted.car_info.SNumber << "#"
				<< _wanted.car_info.SType << "#" << std::fixed << std::setprecision(1) << _wanted.rating << "#" << endl;
			cout << "flag F" << endl;
			output.close();
			cout << ">> file data updeted :D (rating updated), captain " << _wanted.user_data.full_name.firstname << " rating is now " << _wanted.rating << endl;





			cout << "rate complete" << endl;
			MessageBox::Show("Thank you for your feedback, hope to see you again!", "Rating");


			pictureBox17->BringToFront();

		}


		void Load_rider_history()
		{
			fpn_rider_history->Controls->Clear();
			rider_history_rides_count = 0;
			total_rides->Text = "Total rides: " + rider_history_rides_count;

			ifstream data_file("data.txt");


			string data_line;
			string arr[8];
			int ind = 0;


			while (getline(data_file, data_line)) // read every line in history file
			{

				if (data_line[0] == 'H' && data_line[1] == 'R') // get all histroy rides
				{
					string s{};
					for (int i = 0; i < data_line.size(); i++)
					{
						if (data_line[i] == '#')
						{
							arr[ind++] = s;
							cout << "-) " << s << endl;
							s = {};

						}
						else
						{
							s.push_back(data_line[i]);
						}

					}
					ind = 0;

					cout << arr[1] << endl;            // flag

					if (Program_user.user_data.SUser_name == arr[1])
					{

						Ride ride;
						ride.rider.user_data.SUser_name = arr[1];
						ride.captain.user_data.full_name.firstname = arr[2].substr(0, arr[2].find(' '));
						ride.Location = arr[3];
						ride.Distination = arr[4];


					


						 // pushing the history ride as a panel inside the flow panel


						Panel^ newPanel = gcnew Panel();
						newPanel->Size = System::Drawing::Size(607, 116);
						newPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(18)), static_cast<System::Int32>(static_cast<System::Byte>(78)),
							static_cast<System::Int32>(static_cast<System::Byte>(80)));


						/*

			this->label100->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);


						
						*/



						




						// adding captain name label
						Label^ c_name_l = gcnew Label();
						c_name_l->AutoSize = true;
						c_name_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
						c_name_l->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							static_cast<System::Byte>(0)));
						c_name_l->Location = System::Drawing::Point(10, 10);
						c_name_l->Name = L"label20";
						c_name_l->Size = System::Drawing::Size(166, 20);
						c_name_l->TabIndex = 4;
						c_name_l->Text = L"Captain name:";
						newPanel->Controls->Add(c_name_l); // add the label to the panel

						// adding captain name
						Label^ c_name = gcnew Label();
						c_name->AutoSize = true;
						c_name->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
						c_name->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							static_cast<System::Byte>(0)));
						c_name->Location = System::Drawing::Point(170, 10);
						c_name->Name = L"captain_name";
						c_name->Size = System::Drawing::Size(166, 20);
						c_name->TabIndex = 4;
						c_name->Text = gcnew String((ride.captain.user_data.full_name.firstname + " " + ride.captain.user_data.full_name.lastname).c_str()); //
						newPanel->Controls->Add(c_name); // add the label to the panel

						


						//adding location label
						Label^ location_l = gcnew Label();
						location_l->AutoSize = true;
						location_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
						location_l->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							static_cast<System::Byte>(0)));
						location_l->Location = System::Drawing::Point(10, 40);
						location_l->Name = L"label21";
						location_l->Size = System::Drawing::Size(166, 20);
						location_l->TabIndex = 4;
						location_l->Text = gcnew String("Location:"); //
						newPanel->Controls->Add(location_l); // add the label to the panel


						// adding location
						Label^ location = gcnew Label();
						location->AutoSize = true;
						location->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
						location->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							static_cast<System::Byte>(0)));
						location->Location = System::Drawing::Point(170, 40);
						location->Name = L"ride_location";
						location->Size = System::Drawing::Size(150, 30);
						location->TabIndex = 4;
						location->Text = gcnew String(ride.Location.c_str()); //
						newPanel->Controls->Add(location); // add the label to the panel




						// adding distination label
						Label^ ditination_l = gcnew Label();
						ditination_l->AutoSize = true;
						ditination_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
						ditination_l->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							static_cast<System::Byte>(0)));
						ditination_l->Location = System::Drawing::Point(10, 70);
						ditination_l->Name = L"label21";
						ditination_l->Size = System::Drawing::Size(150, 30);
						ditination_l->TabIndex = 4;
						ditination_l->Text = gcnew String("Distination:"); //
						newPanel->Controls->Add(ditination_l); // add the label to the panel


						// adding distination 
						Label^ ditination = gcnew Label();
						ditination->AutoSize = true;
						ditination->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
						ditination->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							static_cast<System::Byte>(0)));
						ditination->Location = System::Drawing::Point(170, 70);
						ditination->Name = L"ride_distination";
						ditination->Size = System::Drawing::Size(150, 30);
						ditination->TabIndex = 4;
						ditination->Text = gcnew String(ride.Distination.c_str()); //
						newPanel->Controls->Add(ditination); // add the label to the panel




						rider_history_rides_count++;
						msclr::interop::marshal_context context;
						total_rides->Text = "Total rides: " + rider_history_rides_count;


						fpn_rider_history->Controls->Add(newPanel);

					}


				}
			}
			data_file.close();

		}

		void Clear_rider_history()
		{
			// file
			ifstream data_file("data.txt");

			string data_line;
			string arr[14];
			int ind = 0;

			int cnt = 0;
			string new_lines[101]; //= new string[1001]; //pointer

			

			while (getline(data_file, data_line)) // read every line in history file
			{

					string s{};
					for (int i = 0; i < data_line.size(); i++)
					{
						if (data_line[i] == '#')
						{
							arr[ind++] = s;
							cout << "-) " << s << endl;
							s = {};

						}
						else
						{
							s.push_back(data_line[i]);
						}

					}
					ind = 0;


					if (!((data_line[0] == 'H' && data_line[1] == 'R' && Program_user.user_data.SUser_name == arr[1]) || data_line.empty()))
					{
						cout << "YES" << endl;
						new_lines[cnt++] = data_line;
						cout << data_line << " (picked) at index " << cnt - 1 << endl;

						cout << ">> CHECK FILES HERE !!" << endl;
					}
					

				
			}
			data_file.close();

			ofstream output("data.txt");
			for (int i = 0; i<(cnt);i++)
			{
				output << new_lines[i] << endl;
				cout << new_lines[i] << " (printed) " << endl;
			}

			// gui
			fpn_rider_history->Controls->Clear();
			rider_history_rides_count = 0;
			total_rides->Text = "Total rides: " + rider_history_rides_count;


			cout << "History cleared successfully!" << endl;
			set_status_message("Your history was cleared successfully!");

			/*
			SR#mohamed12#ali#shaheen#Cairo#Giza#12:25AM#
SR#mohamed12#ali#mohamed#Loxur#Qaha#2:25AM#
SR#ahmed11#mazen#fadel#Loxur#Menia#5:00AM#
SR#ahmed11#alla#kamel#Loxur#Menia#7:00AM#
SR#ahmed11#ahmed#zaky#Loxur#Menia#9:00AM#
HR#makaty25#adham  fares#Cairo#Damietta#
			
			*/

		}



		bool Check_time(string hours, string minutes, string pm_am)
		{
			if (minutes.empty() || hours.empty() || pm_am.empty())
				return 0;

			for (auto i : minutes)
			{
				if (isalpha(i) || i == ' ')
					return 0;
			}
			for (auto i : hours)
			{
				if (isalpha(i) || i == ' ')
					return 0;
			}
		

			int h = System::Convert::ToInt16(gcnew String(hours.c_str()));
			int m = System::Convert::ToInt16(gcnew String(minutes.c_str()));

			if (h >= 24 || h <= 0 || m < 0 || m > 60 || pm_am.empty())
				return 0;

			return 1;



		}







		void set_captain_status_message(string message)
		{
			rider_status_panel->Visible = 1;
			pictureBox33->Visible = 1; //exit
			pictureBox15->Visible = 1;//notification
			label37->Text = gcnew String(message.c_str());
		}



		void OnButtonClick_rider(Object^ sender, EventArgs^ e)
		{

			// Retrieve the button control that was clicked
			Button^ button = dynamic_cast<Button^>(sender);


			// Retrieve the label control in the same panel as the button
			Label^ label = dynamic_cast<Label^>(button->Parent->Controls["rider_name"]); //captain_username
			Label^ username = dynamic_cast<Label^>(button->Parent->Controls["rider_username"]);

			msclr::interop::marshal_context context;
			string name = context.marshal_as<std::string>(label->Text);





			// Display the label text
			
				string msg = "Are you sure you want to Begin the ride with: " + name;
				if (MessageBox::Show(gcnew String(msg.c_str()), "Picking a ride", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
				{
				

					MessageBox::Show("Your ride will begin soon", gcnew String(("User: " + name + ":").c_str()));
					label56->Visible = 0;
					pictureBox13->BringToFront();
					in_a_Ride = 1;

					//ride
					Pending_ride.rider.user_data.full_name.firstname = name.substr(0, name.find(' '));
					Pending_ride.rider.user_data.full_name.lastname = name.substr(name.find(' ') + 1, name.size() - 1);

					cout << "rider name >>" << endl;
					cout << Pending_ride.rider.user_data.full_name.firstname << '#' << endl;
					cout << Pending_ride.rider.user_data.full_name.lastname << '#' << endl;


					Pending_ride.rider.user_data.SUser_name = context.marshal_as<std::string>(username->Text);

				//	Add_to_rider_pending_list(Pending_ride);
					Ride_timer->Start();
					//cout << "ride added to pending list" << endl;



					//->Text = gcnew String(().c_str());
					
					//fpn_captains_around->Controls->Clear();

					////////////////////////////////////////////


				}


			//MessageBox::Show(label->Text);


		}



		void Display_on_riders_list(Rider rider)
		{
			// this will be the pushing to the panel 
			cout << "> rider : " << rider.user_data.full_name.firstname << ' ' << rider.user_data.full_name.lastname << endl;


			msclr::interop::marshal_context context;
			Panel^ newPanel = gcnew Panel();
			newPanel->Size = System::Drawing::Size(289, 77);
			newPanel->BackColor = System::Drawing::SystemColors::WindowFrame;





			// adding rider name label
			Label^ c_name_l = gcnew Label();
			c_name_l->AutoSize = true;
			c_name_l->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			c_name_l->BackColor = System::Drawing::SystemColors::WindowFrame;
			c_name_l->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			c_name_l->Location = System::Drawing::Point(5, 21);
			c_name_l->Name = L"label20";
			c_name_l->Size = System::Drawing::Size(68, 17);
			c_name_l->TabIndex = 3;
			c_name_l->Text = L"Rider name:";
			newPanel->Controls->Add(c_name_l); // add the label to the panel




			// adding rider name
			Label^ c_name = gcnew Label();
			c_name->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			c_name->AutoSize = true;
			c_name->BackColor = System::Drawing::SystemColors::WindowFrame;
			c_name->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			c_name->Location = System::Drawing::Point(94, 21);
			c_name->Name = L"rider_name";
			c_name->Size = System::Drawing::Size(68, 17);
			c_name->TabIndex = 3;
			c_name->Text = gcnew String((rider.user_data.full_name.firstname + " " + rider.user_data.full_name.lastname).c_str()); //
			newPanel->Controls->Add(c_name); // add the label to the panel





			// hiddden username
			Label^ username = gcnew Label();
			username->AutoSize = true;
			username->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			username->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			username->Location = System::Drawing::Point(120, 70);
			username->Name = L"rider_username";
			username->BackColor = System::Drawing::SystemColors::WindowFrame;
			username->Size = System::Drawing::Size(68, 17);
			username->TabIndex = 3;
			username->Visible = 0;
			username->Text = gcnew String(rider.user_data.SUser_name.c_str()); //
			newPanel->Controls->Add(username); // add the label to the panel

			/*
		
			this->button33->
			this->button33->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightGreen;
			this->button33->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			this->button33->Location = System::Drawing::Point(215, 19);
			this->button33->Name = L"button33";
			this->button33->Size = System::Drawing::Size(66, 26);
			this->button33->TabIndex = 19;
			this->button33->Text = L"Pick";
			this->button33->UseVisualStyleBackColor = false;
			// 
			*/

			//adding choose button
			Button^ choose = gcnew Button;
			choose->BackColor = System::Drawing::SystemColors::ScrollBar;
			choose->FlatAppearance->BorderColor = System::Drawing::Color::White;
			choose->Cursor = System::Windows::Forms::Cursors::Hand;
			choose->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightGreen;
			choose->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			choose->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			choose->Location = System::Drawing::Point(220, 48);
			choose->Name = L"choose_by_me";
			choose->Size = System::Drawing::Size(66, 26);
			choose->TabIndex = 19;
			choose->Text = L"Pick";
			choose->UseVisualStyleBackColor = false;

			choose->Click += gcnew EventHandler(this, &MyForm::OnButtonClick_rider);

			newPanel->Controls->Add(choose);

			fpn_riders_around->Controls->Add(newPanel);
		}


		void Search_riders_around_me()
		{

			system("cls");
			srand(time(0));


			// note than i spent 12 hour writing this logic, if u change it u return it (:D
			string location = Program_user.user_data.SCity_location;
			string rider_loc = '#' + location + '#';
			int random_count = rand() % (Riders_count+1); // 4 - > 2

			
			cout << "*The Riders Around your Location*\n";

			ifstream data_file("account_info.txt");
			string data_line;
			while (getline(data_file, data_line))
			{

				//random_captains_count--;
				//cout << "random captain found !" << endl;

				// translating . . .
				string s{};
				string arr[13];
				int ind = 0;
				for (int i = 0; i < data_line.size(); i++)
				{
					if (data_line[i] == '#')
					{
						arr[ind++] = s;
						s = {};

					}
					else
					{
						s.push_back(data_line[i]);
					}

				}
				cout << random_count << endl;
				//checking . . 
				cout << ">>" << arr[6] << endl;
				if (arr[2] == "R" && random_count > 0)
				{

					//collecting..

					Rider rider;
					rider.user_data.SUser_name = arr[0];
					rider.user_data.SPassword = arr[1];
					rider.user_data.SID = arr[3];
					rider.user_data.full_name.firstname = arr[4];
					rider.user_data.full_name.lastname = arr[5];

					Display_on_riders_list(rider);


					random_count--;
				}
				else if (random_count <= 0) break;




				/*if (arr[2] == "R" && random_count <= 0)
				{

					
						
				}
				else if (arr[2] == "R")
				{

					random_count--;*/



			}



		}

		

	
		

		
		void Change_my_rate(int rating)
		{
			//for captain
			//files part
			// 
			// editing data in file
			cout << "flag A" << endl;

			Captain _wanted;

			ifstream data_file("account_info.txt");

			string file_lines[51];
			int cnt = 0;
			string line;
			while (getline(data_file, line))
			{
				string arr[20];
				string s{};
				int arr_ind = 0;
				for (int i = 0; i < line.size(); i++)
				{
					if (line[i] == '#')
					{
						arr[arr_ind++] = s;
						s = {};

					}
					else
					{
						s.push_back(line[i]);
					}

				}

				if (arr[0] != Program_user.user_data.SUser_name)
				{
					file_lines[cnt++] = line;
				}
				else
				{
					cout << "flag B" << endl;
					// record data for the wanted captain // me
					_wanted.user_data.SUser_name = arr[0];
					cout << _wanted.user_data.SUser_name << endl;
					_wanted.user_data.SPassword = arr[1];
					//_wanted.role = arr[2];
					_wanted.user_data.SID = arr[3];
					_wanted.user_data.full_name.firstname = arr[4];
					_wanted.user_data.full_name.lastname = arr[5];
					_wanted.user_data.SCity_location = arr[6];
					cout << "flag B1" << endl;
					_wanted.car_info.SColor = arr[7];
					_wanted.car_info.ILevel = arr[8];
					_wanted.car_info.SNumber = arr[9];
					_wanted.car_info.SType = arr[10];
					cout << "flag B2" << endl;
					cout << ".editing my rate." << arr[11] << endl;
					_wanted.rating = stof(arr[11]); // trans. from string 2.32 to float
					cout << "flag B3" << endl;
					float current_rating = _wanted.rating;
					float edited_rating;
					cout << "flag C" << endl;

					cout << ">>current rating for " << _wanted.user_data.full_name.firstname << ' ' << _wanted.user_data.full_name.lastname << " is " << current_rating << endl;
					if (rating == 1)
					{
						if (current_rating >= 0.8)
						{
							edited_rating = current_rating - 0.3;

						}
						else
						{
							edited_rating = 0.5;
						}

					}
					else if (rating == 2)
					{
						if (current_rating >= 0.8)
						{
							edited_rating = current_rating - 0.2;

						}
						else
						{
							edited_rating = 0.5;
						}

					}
					else if (rating == 3)
					{
						if (current_rating >= 2.5)
						{
							edited_rating = current_rating - 0.2;

						}
						else if (current_rating <= 4.8)
						{
							edited_rating = current_rating + 0.2;
						}

					}
					else if (rating == 4)
					{
						if (current_rating < 4.7)
						{
							edited_rating = current_rating + 0.3;

						}
						else if (current_rating <= 4.9)
						{
							edited_rating = current_rating + 0.1;
						}


					}
					else //5
					{
						if (current_rating <= 4.5)
						{
							edited_rating = current_rating + 0.5;

						}
						else if (current_rating <= 4)
						{
							edited_rating = current_rating + 1.0;
						}
						else
						{
							edited_rating = current_rating;
						}

					}
					cout << "flag D" << endl;
					_wanted.rating = edited_rating;
					label29->Text = "Rating: " + edited_rating.ToString("0.0");
					Program_user.rating = edited_rating;
					//// = ("Rating: " + );
					
					
					

					cout << "new rating: " << edited_rating << endl;
					cout << "flag E" << endl;




				}


			}
			data_file.close();


			ofstream output("account_info.txt");
			//output << Riders_count << "R&" << Captains_count << "C" << endl;

			// other data
			for (int i = 0; i <(cnt); i++)
			{
				output << file_lines[i] << endl;
			}
			cout << "flag E" << endl;

			// re enter the edited data line
			output << _wanted.user_data.SUser_name << "#" << _wanted.user_data.SPassword << "#"
				<< "C" << "#" << _wanted.user_data.SID << "#" << _wanted.user_data.full_name.firstname << "#"
				<< _wanted.user_data.full_name.lastname << "#" << _wanted.user_data.SCity_location << "#"
				<< _wanted.car_info.SColor << "#" << _wanted.car_info.ILevel << "#" << _wanted.car_info.SNumber << "#"
				<< _wanted.car_info.SType << "#" << std::fixed << std::setprecision(1) << _wanted.rating << "#" << endl;
			cout << "flag F" << endl;
			output.close();
			cout << ">> file data updeted :D (rating updated), (my rate) " << _wanted.user_data.full_name.firstname << " my rating is now " << _wanted.rating << endl;





			cout << "rate complete" << endl;
			//MessageBox::Show("Thank you for your feedback, hope to see you again!", "Rating");


			//pictureBox35->BringToFront();

		}




		void Remove_from_data(string location, string distination, string time)
		{
			ifstream data_file("data.txt");
			string data_line;
			string new_lines[101];
			int cnt = 0;

			while (getline(data_file, data_line))
			{
				if ((data_line.find(('#' + location + '#')) != string::npos && data_line.find(('#' + distination + '#')) != string::npos && data_line.find(('#' + time + '#')) != string::npos)) // if its not the wanted ride we delete it cz its the wanted to be deleted
				{
					

				}
				else
				{
					new_lines[cnt++] = data_line;
					cout << data_line << " (picked) at index " << cnt - 1 << endl;
				}
			}
			data_file.close();

			ofstream output("data.txt");
			for (int i = 0; i < (cnt); i++)
			{
				output << new_lines[i] << endl;
				cout << new_lines[i] << " (printed) " << endl;
			}

		

		}


		void Remove_scheduled_ride_from_files(Ride ride)
		{
			ifstream data_file("data.txt");
			string data_line;
			string new_lines[101];
			int cnt = 0;

			while (getline(data_file, data_line))
			{
				if (!(data_line.find("SR") != string::npos && data_line.find(('#' + ride.captain.user_data.SUser_name + '#')) != string::npos && data_line.find(('#' + ride.rider.user_data.SUser_name + '#')) != string::npos)) // if its not the wanted ride we delete it cz its the wanted to be deleted
				{

					new_lines[cnt++] = data_line;
					cout << data_line << " (picked) at index " << cnt - 1 << endl;

				}
				
			}
			data_file.close();


			ofstream output("data.txt");
			for (int i = 0; i < (cnt); i++)
			{
				output << new_lines[i] << endl;
				cout << new_lines[i] << " (printed) " << endl;
			}
			cout << " ^^ Check if SR deleted? " << endl;
		}


		bool dragging = 0;
		Point offset;
		int cnt = 0;
		int exit = 0;

	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		pictureBox21->BringToFront();
		timer2->Start();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->WindowState == FormWindowState::Maximized)
		{
			this->WindowState = FormWindowState::Normal;
		}
		else
			this->WindowState = FormWindowState::Maximized;
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		this->WindowState = FormWindowState::Minimized;
	}
	private: System::Void pn_bar_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pn_bar_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		dragging = 1;
		offset.X = e->X;
		offset.Y = e->Y;

	}
	private: System::Void pn_bar_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		dragging = 0;
	}
	private: System::Void pn_bar_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (dragging)
		{
			Point current = PointToScreen(Point(e->X, e->Y));
			Location = Point(current.X - offset.X, current.Y - offset.Y);
		}
	}

	private: System::Void button2_Click_1(System::Object^ sender, System::EventArgs^ e) {
		pn_login_screan->BringToFront();
	}

	private: System::Void pictureBox6_Click(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_start->BringToFront();
	}
	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_terms->BringToFront();
	}
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_riderRe->BringToFront();
	}
	private: System::Void pn_terms_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_Register->BringToFront();
	}
	private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_login_screan->BringToFront();
	}
	private: System::Void textBox4_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label10_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void flowLayoutPanel2_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void textBox5_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button12_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_Register->BringToFront();
	}
	private: System::Void pictureBox10_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void checkBox1_CheckedChanged_1(System::Object^ sender, System::EventArgs^ e) {
		if (checkBox1->Checked)
		{
			button11->Enabled = 1;
		}
		else if (checkBox1->Checked == 0)
		{
			button11->Enabled = 0;
		}
	}
	private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_riderRe->BringToFront();
	}
	private: System::Void label5_Click_1(System::Object^ sender, System::EventArgs^ e) {
		pn_terms->BringToFront();
	}

	private: System::Void button11_Click(System::Object^ sender, System::EventArgs^ e) {
		//pn_riderMenu->BringToFront();
		// rider register
		msclr::interop::marshal_context context;

		string username = context.marshal_as<std::string>(textBox6->Text);
		string password = context.marshal_as<std::string>(textBox7->Text);
		string firstname = context.marshal_as<std::string>(textBox4->Text);
		string lastname = context.marshal_as<std::string>(textBox5->Text);
		string id = context.marshal_as<std::string>(textBox8->Text);

		string error;


		if (Check_firstname(firstname, &error) &&
			Check_lastname(lastname, &error) &&
			Check_username(username, &error) &&
			Check_password(password, &error) &&
			Check_id(id, &error))
		{
			// performing registeration . . .
			rider_r_error->Visible = 0;

			cout << "Registeration success :) (rider)" << endl;
			Register_user(firstname, lastname, username, password, id);

			button11->Enabled = 0;
			loading_gifr->Visible = 1;
			loading_timer->Start();


		}
		else
		{
			// username error
			if (!Check_firstname(firstname, &error)) // firstname error
			{
				if (error == "empty")
					rider_r_error->Text = "Please enter your firstname!";
				else if (error == "special_char")
					rider_r_error->Text = "Your firstname can't contains special characters or digits!";
				error.clear();
			}
			else if (!Check_lastname(lastname, &error)) // lastname error
			{
				if (error == "empty")
					rider_r_error->Text = "Please enter your lastname!";
				else if (error == "special_char")
					rider_r_error->Text = "Your lastname can't contains special characters or digits!";
				error.clear();
			}
			else if (!Check_username(username, &error))
			{
				if (error == "empty")
					rider_r_error->Text = "Please enter your username!";
				else if (error == "begin_num")
					rider_r_error->Text = "Usename can't contains degits at beginning!";
				else if (error == "special_char")
					rider_r_error->Text = "Usename can't contains special characters except '_'!";
				else if (error == "alredy_exists")
					rider_r_error->Text = "This username already exists, please try another!";

				error.clear();

			}
			else if (!Check_password(password, &error)) // password error
			{
				if (error == "empty")
					rider_r_error->Text = "Please enter your password!";
				else if (error == "less_th_8")
					rider_r_error->Text = "Your password must be at least 8 characters!";
				else if (error == "have_spaces")
					rider_r_error->Text = "Your password can't caontains spaces!";
				error.clear();
			}
			else if (!Check_id(id, &error)) // ID error
			{
				if (error == "empty")
					rider_r_error->Text = "Please enter your ID number!";
				else if (error == "less_th_14")
					rider_r_error->Text = "Your ID must be 14 digits!";
				else if (error == "special_char")
					rider_r_error->Text = "Your ID can't contains special characters!";
				error.clear();
			}


			rider_r_error->Visible = 1;


		}


	}
	private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_captinRe->BringToFront();
	}
	private: System::Void button13_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_Register->BringToFront();
	}
	private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button15_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_captinRe->BringToFront();
	}
	private: System::Void label25_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_terms2->BringToFront();
	}
	private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (checkBox2->Checked)
		{
			button14->Enabled = 1;
		}
		else if (checkBox2->Checked == 0)
		{
			button14->Enabled = 0;
		}
	}
	private: System::Void pictureBox12_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button14_Click(System::Object^ sender, System::EventArgs^ e) {

		msclr::interop::marshal_context context;

		string username = context.marshal_as<std::string>(textBox11->Text);
		string password = context.marshal_as<std::string>(textBox10->Text);
		string firstname = context.marshal_as<std::string>(textBox13->Text);
		string lastname = context.marshal_as<std::string>(textBox12->Text);
		string car_number = context.marshal_as<std::string>(textBox14->Text);

		string id = context.marshal_as<std::string>(textBox9->Text);
		string car_level = context.marshal_as<std::string>(comboBox11->Text);
		string car_color = context.marshal_as<std::string>(comboBox2->Text);
		string car_type = context.marshal_as<std::string>(comboBox1->Text);
		string location = context.marshal_as<std::string>(comboBox12->Text);

		string error;
		if (Check_firstname(firstname, &error) &&
			Check_lastname(lastname, &error) &&
			Check_username(username, &error) &&
			Check_password(password, &error) &&
			Check_id(id, &error) &&
			Check_captain_plate(car_number, &error) &&
			Check_captain_level(car_level, &error) &&
			Check_captain_color(car_color, &error) &&
			Check_captain_location(location, &error) &&
			Check_captain_type(car_type, &error))
		{
			// performing registeration . . .
			captain_r_error->Visible = 0;
			cout << "Registeration success :)" << endl;
			Register_user(firstname, lastname, username, password, id, car_number, car_level, car_color, car_type, location);

			button14->Enabled = 0;
			loading_gifc->Visible = 1;
			loading_timer->Start();


		}
		else
		{
			// username error
			if (!Check_firstname(firstname, &error)) // firstname error
			{
				if (error == "empty")
					captain_r_error->Text = "Please enter your firstname!";
				else if (error == "special_char")
					captain_r_error->Text = "Your firstname can't contains special characters or digits!";
				error.clear();
			}
			else if (!Check_lastname(lastname, &error)) // lastname error
			{
				if (error == "empty")
					captain_r_error->Text = "Please enter your lastname!";
				else if (error == "special_char")
					captain_r_error->Text = "Your lastname can't contains special characters or digits!";
				error.clear();
			}
			else if (!Check_username(username, &error))
			{
				if (error == "empty")
					captain_r_error->Text = "Please enter your username!";
				else if (error == "begin_num")
					captain_r_error->Text = "Usename can't contains degits at beginning!";
				else if (error == "special_char")
					captain_r_error->Text = "Usename can't contains special characters except '_'!";
				else if (error == "alredy_exists")
					captain_r_error->Text = "This username already exists, please try another!";

				error.clear();

			}
			else if (!Check_password(password, &error)) // password error
			{
				if (error == "empty")
					captain_r_error->Text = "Please enter your password!";
				else if (error == "less_th_8")
					captain_r_error->Text = "Your password must be at least 8 characters!";
				else if (error == "have_spaces")
					captain_r_error->Text = "Your password can't caontains spaces!";
				error.clear();
			}
			else if (!Check_id(id, &error)) // ID error
			{
				if (error == "empty")
					captain_r_error->Text = "Please enter your ID number!";
				else if (error == "less_th_14")
					captain_r_error->Text = "Your ID must be 14 digits!";
				else if (error == "special_char")
					captain_r_error->Text = "Your ID can't contains special characters!";
				error.clear();
			}
			else if (!Check_captain_type(car_type, &error)) // car number error
			{
				captain_r_error->Text = "Please enter your car type!"; error.clear();
			}
			else if (!Check_captain_color(car_color, &error)) // car number error
			{
				captain_r_error->Text = "Please enter your car color!"; error.clear();
			}
			else if (!Check_captain_level(car_level, &error)) // car number error
			{
				captain_r_error->Text = "Please enter your car level!"; error.clear();
			}
			else if (!Check_captain_plate(car_number, &error)) // car number error
			{
				if (error == "empty")
					captain_r_error->Text = "Please enter your car number!";
				else if (error == "not_6" || error == "sorting")
					captain_r_error->Text = "Your car number must be 3 digits followed by three capital characters!";
				else if (error == "not_6" || error == "sorting")
					captain_r_error->Text = "Your car number must be 3 digits followed by three capital characters!";
				error.clear();
			}
			else if (!Check_captain_location(location, &error)) // location error
			{
				captain_r_error->Text = "Please enter your location!";
				error.clear();
			}





			captain_r_error->Visible = 1;


		}




	}
	private: System::Void label26_Click(System::Object^ sender, System::EventArgs^ e) {
		label26->Text = textBox13->Text;
	}
	private: System::Void label27_Click(System::Object^ sender, System::EventArgs^ e) {
		label27->Text = textBox12->Text;
	}
	private: System::Void button16_Click(System::Object^ sender, System::EventArgs^ e) {

		// empty elements
		textBox18->Text = "";
		comboBox8->SelectedIndex = -1;
		comboBox9->SelectedIndex = -1;
		comboBox10->SelectedIndex = -1;//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		label_error->Visible = 0;
		pn_login_screan->BringToFront();
		textBox2->Clear();
		textBox3->Clear();
		label64->Visible = 0;

		cout << "flag7" << endl;
		Program_user = {};
		fpn_schedule_requests->Controls->Clear();
	}
	private: System::Void button17_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_schedule_requests->BringToFront();
		fpn_schedule_requests->Controls->Clear();

		Display_captain_Schedule_requests();

	}
	private: System::Void button18_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_carInfo->BringToFront();
	}
	private: System::Void button19_Click(System::Object^ sender, System::EventArgs^ e) {
		pictureBox13->BringToFront();
	}
	private: System::Void textBox13_TextChanged(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void button21_Click(System::Object^ sender, System::EventArgs^ e) {
		pictureBox21->BringToFront();
		timer2->Start();
	}


	private: System::Void button27_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!is_choosing_a_rate)
		{
			pictureBox17->BringToFront();
		}
		else
		{
			set_status_message("Please rate your captain before you end the ride ");
		}
		
	}
	private: System::Void button26_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!is_choosing_a_rate)
		{
			label64->Visible = 0;
			pn_login_screan->BringToFront();
		}
		else
		{
			set_status_message("Please rate your captain before you end the ride ");
		}
		
	}
	private: System::Void button22_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!is_choosing_a_rate)
		{
			making_schedule_ride = 0;
			pn_requestRide->BringToFront();
		}
		else
		{
			set_status_message("Please rate your captain before you end the ride ");
		}
		
	}
	private: System::Void button23_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!is_choosing_a_rate)
		{
			making_schedule_ride = 1;
			pn_scheduleRide->BringToFront();

		}
		else
		{
			set_status_message("Please rate your captain before you end the ride ");
		}
	}
	private: System::Void button24_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!is_choosing_a_rate)
		{
			pn_penddingList->BringToFront();

		}
		else
		{
			set_status_message("Please rate your captain before you end the ride ");
		}
	}
	private: System::Void button25_Click(System::Object^ sender, System::EventArgs^ e) {

		if (!is_choosing_a_rate)
		{
			Load_rider_history();
			pn_viewHistory->BringToFront();

		}
		else
		{
			set_status_message("Please rate your captain before you end the ride ");
		}
	}
	


	private: System::Void button20_Click(System::Object^ sender, System::EventArgs^ e) {

		msclr::interop::marshal_context context;
		string location = context.marshal_as<std::string>(comboBox3->Text);
		string distination = context.marshal_as<std::string>(comboBox4->Text);
		string level = context.marshal_as<std::string>(comboBox13->Text);
		string error;

		if (Check_captain_level(level, &error) && Check_captain_location(location, &error) && Check_captain_location(distination, &error) && !in_a_Ride)
		{
			req_error->Visible = 0;


			fpn_captains_around->Visible = 1;
			label56->Visible = 1;
			pn_captains_around->BringToFront();

			set_pending_ride(level, location, distination);

			cout << "request a ride completed :)" << endl;

			cout << "here are the captains around your location :D (can be empty)" << endl;

			refresh_captains->PerformClick();
			//Search_captains_around(Pending_ride.Location);

			refresh_captains->Visible = 1;




		}
		else
		{
			if (!Check_captain_location(location, &error))
				req_error->Text = "Please enter your location!";
			else if (!Check_captain_location(distination, &error))
				req_error->Text = "Please enter your distination!";
			else if (!Check_captain_level(level, &error))
				req_error->Text = "Please enter your desired car level!";
			else req_error->Text = "Please note that you are alrady in a ride";

			req_error->Visible = 1;

		}



	}
	private: System::Void button28_Click(System::Object^ sender, System::EventArgs^ e) {
		pictureBox19->BringToFront();
		timer1->Start();
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (cnt == 10)
		{
			cnt = 0;
			pictureBox17->BringToFront();
			timer1->Stop();
		}
		else
		{
			cnt++;
		}

	}
	private: System::Void button29_Click(System::Object^ sender, System::EventArgs^ e) {
		pictureBox17->BringToFront();
	}
	private: System::Void timer2_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (exit == 10)
		{
			exit = 0;
			Environment::Exit(0);
			timer2->Stop();
		}
		else
		{
			exit++;
		}
	}
	private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {

		string username, password;
		msclr::interop::marshal_context context;
		username = context.marshal_as<std::string>(textBox2->Text);
		password = context.marshal_as<std::string>(textBox3->Text);
		cout << username << endl << password << endl;

		if (Check_account(username, password))
		{
			cout << "flag1" << endl;
			
			
			Set_user_data_fill(username, password);
			

			if (Program_user.role == "C")
			{
				// the user is a captain
				
				pictureBox35->BringToFront();
				pn_captainMenu->BringToFront();
				
				//pictureBox13->BringToFront();
				cout << "captain" << endl;

				label65->Text = gcnew String((Program_user.user_data.full_name.firstname + ' ' + Program_user.user_data.full_name.lastname).c_str());
				cout << ">>>" << Program_user.user_data.full_name.firstname << endl;
				label26->Text = gcnew String(Program_user.user_data.full_name.firstname.c_str());
				label27->Text = gcnew String(Program_user.user_data.full_name.lastname.c_str());
				label32->Text = gcnew String(("Type: " + Program_user.car.SType).c_str()); // type
				label33->Text = gcnew String(("Color: " + Program_user.car.SColor).c_str()); // color
				label34->Text = gcnew String(("Plat: " + Program_user.car.SNumber).c_str());
				label35->Text = gcnew String(("Level: " + Program_user.car.ILevel).c_str());

				label43->Text = gcnew String(Program_user.car.SType.c_str());
				label45->Text = gcnew String(Program_user.car.SNumber.c_str());
				label44->Text = gcnew String(Program_user.car.SColor.c_str());
				label46->Text = gcnew String(Program_user.car.ILevel.c_str());

				label77->Text = gcnew String(Program_user.user_data.SID.c_str());
				label78->Text = gcnew String(Program_user.user_data.SCity_location.c_str());
				label79->Text = gcnew String(Program_user.user_data.SUser_name.c_str());
				label29->Text = "Rating: " + Program_user.rating.ToString("0.0");

				cout << std::fixed << std::setprecision(2) << "Rating: " << Program_user.rating << endl;
				



			}
			else
			{
				// the user is a rider
				//Set_user_data_fill(username, password, "R");
				Set_rider_profile();
				//captain_fullname->Text = gcnew String((Program_user.user_data.full_name.firstname + ' ' + Program_user.user_data.full_name.lastname).c_str());
				pictureBox17->BringToFront();
				pn_riderMenu->BringToFront();
				
				cout << "rider" << endl;

			}
			cout << "login success! :)" << endl;
			textBox2->Text = "";
			textBox3->Text = "";
			

			cout << "wanted flag" << endl;

			clock->Start();

		}
		else
		{
			cout << "login fail! " << endl;
			cout <<"username: " <<  Program_user.user_data.SUser_name << endl;
			label64->Visible = 1;

		}


	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		pn_start->BringToFront();
		Get_counts();

	}
	private: System::Void textBox2_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyValue == (int)Keys::Enter)
		{
			textBox3->Focus();

		}
	}
	private: System::Void textBox3_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyValue == (int)Keys::Enter)
		{
			button7->PerformClick();
		}
	}
	private: System::Void button30_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_profile->BringToFront();
	}
	private: System::Void label44_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button31_Click(System::Object^ sender, System::EventArgs^ e) {

		fpn_schedule_requests->Controls->Clear();
		msclr::interop::marshal_context context;
		string plate_num = context.marshal_as<std::string>(textBox18->Text);

		// check car number
		if (Check_plate_number(plate_num) && comboBox8->SelectedIndex >= 0 && comboBox9->SelectedIndex >= 0 && comboBox10->SelectedIndex >= 0)
		{
			// check tyoe combo box
			cout << "correct details :)" << endl;
			MessageBox::Show("Success!", "note");

			//logic
			string plate = context.marshal_as<std::string>(textBox18->Text);
			string type = context.marshal_as<std::string>(comboBox9->Text);
			string color = context.marshal_as<std::string>(comboBox8->Text);
			string level = context.marshal_as<std::string>(comboBox10->Text);

			Edit_car_info(plate, type, color, level);
			label_error->Visible = 0;



		}
		else
		{
			if (!Check_plate_number(plate_num))
			{
				label_error->Text = "Please Enter a valid car number which have 3 digits followed by three capital litters!";
			}
			else
			{

				label_error->Text = "Please Enter a valid car information!";
			}

			label_error->Visible = 1;
			cout << "invalide details :( " << endl;

		}
	}
	private: System::Void pn_profile_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void clock_Tick(System::Object^ sender, System::EventArgs^ e) {

		System::DateTime time_now = System::DateTime::Now;
		captain_clock->Text = time_now.ToString("hh:mm:tt");
		rider_clock->Text = time_now.ToString("hh:mm:tt");

		


	}


		   // check password strength
		   void updatePasswordStrength(String^ password, ProgressBar^ progress_bar)
		   {
			   int score = 0;
			   int length = password->Length;

			   if (length > 7)
				   score += 25;
			   // check if the text contains A to Z or other conditions
			   if (System::Text::RegularExpressions::Regex::IsMatch(password, "[a-z]"))
				   score += 25;

			   if (System::Text::RegularExpressions::Regex::IsMatch(password, "[A-Z]"))
				   score += 25;

			   if (System::Text::RegularExpressions::Regex::IsMatch(password, "[0-9]"))
				   score += 25;

			   if (System::Text::RegularExpressions::Regex::IsMatch(password, "[^a-zA-Z0-9]"))
				   score += 25;

			   if (score < progress_bar->Maximum / 2) {
				   progress_bar->ForeColor = Color::Red;
			   }
			   else {
				   progress_bar->ForeColor = Color::Green;
			   }
			   progress_bar->Value = score;
		   }

	private: System::Void textBox10_TextChanged(System::Object^ sender, System::EventArgs^ e) {

		updatePasswordStrength(textBox10->Text, progressBar1);
	}
	private: System::Void textBox7_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		updatePasswordStrength(textBox7->Text, progressBar2);

	}
	private: System::Void loading_timer_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (cnt >= 20 + rand() % 20)
		{
			// open




			cnt = 0;
			loading_gifr->Visible = 0;
			loading_gifc->Visible = 0;
			pn_login_screan->BringToFront();

			//background
			Clear_rider_register_boxes();
			Clear_captain_register_boxes();

			loading_timer->Stop();
			MessageBox::Show("You have been registered successfully,\nyou can now login with your account.", "Registeration completed");

		}
		else cnt++;

		cout << "cnt: " << cnt << endl;

	}

	private: System::Void textBox13_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {

		if (e->KeyChar == (char)Keys::Enter)
		{
			e->Handled = true;
			textBox12->Focus();

		}
	}
	private: System::Void textBox12_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter)
		{
			e->Handled = true;
			textBox11->Focus();

		}
	}
	private: System::Void textBox11_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter)
		{
			e->Handled = true;
			textBox10->Focus();

		}
	}
	private: System::Void textBox10_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter)
		{
			e->Handled = true;
			textBox9->Focus();

		}
	}
	private: System::Void textBox9_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter)
		{
			e->Handled = true;
			comboBox1->Focus();

		}
	}
	private: System::Void textBox14_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter)
		{
			e->Handled = true;
			comboBox12->Focus();

		}
	}
	private: System::Void textBox4_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) { //firstname//

		if (e->KeyChar == (char)Keys::Enter)
		{

			e->Handled = true;
			textBox5->Focus();

		}

	}
	private: System::Void textBox5_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) { //lastname
		if (e->KeyChar == (char)Keys::Enter)
		{

			e->Handled = true;
			textBox6->Focus();

		}
	}
	private: System::Void textBox6_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {//username
		if (e->KeyChar == (char)Keys::Enter)
		{
			e->Handled = true;
			textBox7->Focus();

		}
	}
	private: System::Void textBox7_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {//password
		if (e->KeyChar == (char)Keys::Enter)
		{
			e->Handled = true;
			textBox8->Focus();

		}
	}
	private: System::Void textBox8_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {//ID
		if (e->KeyChar == (char)Keys::Enter)
		{
			e->Handled = true;
			button11->PerformClick();

		}

	}

	private: System::Void textBox2_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter)
		{
			e->Handled = true;
			textBox3->Focus();

		}
	}
	private: System::Void textBox3_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter)
		{
			e->Handled = true;
			button7->PerformClick();

		}
	}
	private: System::Void comboBox13_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pn_captains_around_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {




	}
	private: System::Void pn_around_captain_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}

	private: System::Void pictureBox27_Click(System::Object^ sender, System::EventArgs^ e) {
		status_panel->Visible = 0;
	}
	private: System::Void pictureBox28_Click(System::Object^ sender, System::EventArgs^ e) {
		if (status_panel->Visible == 0) // if hidden
		{
			pictureBox29->Visible = 0;
			pictureBox27->Visible = 0;
			status_message->Text = "You have no notifications";
			status_panel->Visible = 1;
		}
		else
		{
			cout << "wanted!" << endl;
			status_panel->Visible = 0;

		}
	}
	private: System::Void refresh_captains_Click(System::Object^ sender, System::EventArgs^ e) {
		cout << "refreshing" << endl;
		refresh_anim->Visible = 1;
		refreshing_timer->Start();

	}
		   int refresh_cnt = 0;
	private: System::Void refreshing_timer_Tick(System::Object^ sender, System::EventArgs^ e) {
		cout << "refresh_cnt : " << refresh_cnt << endl;
		if (refresh_cnt >= (1 + rand() % 5))
		{
			refresh_cnt = 0;


			fpn_captains_around->Controls->Clear();
			Search_captains_around(Pending_ride.Location);
			refresh_anim->Visible = 0;
			refreshing_timer->Stop();
		}
		else
		{
			refresh_cnt++;
		}
	}
	private: System::Void label90_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label92_Click(System::Object^ sender, System::EventArgs^ e) {
	}

		   int Ride_time = 0;
	private: System::Void Ride_timer_Tick(System::Object^ sender, System::EventArgs^ e) {

		if (!in_a_Ride)
		{
			Ride_timer->Stop();
			pictureBox17->BringToFront();
			Ride_time = 0;
		}

		if (Ride_time >= (10 + rand() % 5))
		{
			if (Program_user.role == "R")
			{
				is_choosing_a_rate = 1;
				set_status_message("Your ride completed");
				pictureBox17->BringToFront();
				in_a_Ride = 0;
				Ride_time = 0;
				fpn_pendingList->Controls->Clear();
				pn_rate_captain->BringToFront();


				Add_to_history(Pending_ride);
			}
			else
			{
				//set_captain_status_message("Your ride with  " + name + " completed");
				int rate = 1 + rand() % 5;
				cout << "rate: " << rate << endl;


				set_captain_status_message("Your ride completed with a rate of " + std::to_string(rate));
				Change_my_rate(rate);
				pictureBox35->BringToFront();
				fpn_riders_around->Controls->Clear();
				in_a_Ride = 0;
				Ride_time = 0;
				//Rate_captain()



			}

			Ride_timer->Stop();
		}
		else
		{
			Ride_time++;
		}

	}
private: System::Void btn_ok_Click(System::Object^ sender, System::EventArgs^ e) {

	if (comboBox14->SelectedIndex >= 0)
	{
		rating_error->Visible = 0;
		msclr::interop::marshal_context context;
		string rating = context.marshal_as<std::string>(comboBox14->Text);
		int acctual_rating = rating[0] - '0';
		Change_captain_rating(acctual_rating);
		comboBox14->SelectedIndex = -1;
		is_choosing_a_rate = 0;
		clear_rider_status_message();

	}
	else
	{
		rating_error->Text = "Please enter a rating for the captain";
		rating_error->Visible = 1;

	}

		


	 
}







private: System::Void panel3_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
}
private: System::Void btn_rider_profile_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!is_choosing_a_rate)
	{
		pn_rider_profile->BringToFront();
	}
	else
	{
		set_status_message("Please rate your captain before you end the ride ");
	}
}
private: System::Void pn_rider_profile_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
}
private: System::Void label62_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void btn_save_Click(System::Object^ sender, System::EventArgs^ e) {

	msclr::interop::marshal_context context;
	string rating = context.marshal_as<std::string>(comboBox14->Text);
	string location = context.marshal_as<std::string>(comboBox6->Text);
	string distination = context.marshal_as<std::string>(comboBox5->Text);
	string level = context.marshal_as<std::string>(comboBox7->Text);

	 s_hours = context.marshal_as<std::string>(textBox15->Text);
	 s_minutes = context.marshal_as<std::string>(textBox16->Text);
	 s_ampm = context.marshal_as<std::string>(_ampm->Text);

	string error;


	if (Check_captain_location(location, &error) && Check_captain_location(distination, &error) && Check_captain_level(level, &error) && Check_time(s_hours, s_minutes, s_ampm))
	{
		label104->Visible = 0;

		


		fpn_captains_around->Visible = 1;
		label56->Visible = 1;
		pn_captains_around->BringToFront();

		set_pending_ride(level, location, distination);
		making_schedule_ride = 1;

		//cout << "request a ride completed :)" << endl;

		cout << "here are the captains around your location :D (can be empty)" << endl;

		Search_captains_around(Pending_ride.Location);

		refresh_captains->Visible = 1;
		//Add_to_rider_schedule_list(location, distination, level, hours, minutes, ampm);
		
	}
	else
	{
		if (!Check_captain_location(location, &error))
		{
			label104->Text = "Please enter your location";


		}
		else if (!Check_captain_location(distination, &error))
		{
			label104->Text = "Please enter your distination";
		}
		else if (!Check_captain_level(level, &error))
		{
			label104->Text = "Please enter your desired car level";
		}
		else
		{
			label104->Text = "Please enter a valid time";
		}


		label104->Visible = 1;

	}



}
private: System::Void btn_schedule_list_Click(System::Object^ sender, System::EventArgs^ e) {

	if (!is_choosing_a_rate)
	{
		pn_rider_schedule_list->BringToFront();
	}
	else
	{
		set_status_message("Please rate your captain before you end the ride ");
	}

	
}
private: System::Void check_schedule_timer_Tick(System::Object^ sender, System::EventArgs^ e) {

	//ride.Sum_time
	// 
	// 
	// 
	// 
	// Get the current time from the time label outside the flow layout panel
	String^ current_time = rider_clock->Text;
	String^ current_time_c = captain_clock->Text;


	msclr::interop::marshal_context context;
	cout << "current time: " << context.marshal_as<std::string>(current_time) << endl; //flag

	if (Program_user.role == "C")
	{

		for (int i = 0; i < fpn_schedule_requests->Controls->Count; i++)
		{
			Panel^ panel = dynamic_cast<Panel^>(fpn_schedule_requests->Controls[i]);

			// get the time label on the panel
			//Label^ timeLabelOnPanel = dynamic_cast<Label^>(panel->Controls["timeLabel"]);

			//captain_name

			Label^ timeLabelOnPanel = dynamic_cast<Label^>(panel->Controls["timeLabel"]);
			Label^ captain_name = dynamic_cast<Label^>(panel->Controls["captain_name"]);
			Label^ ride_location = dynamic_cast<Label^>(panel->Controls["ride_location"]);
			Label^ ride_distination = dynamic_cast<Label^>(panel->Controls["ride_distination"]);
			Label^ c_username = dynamic_cast<Label^>(panel->Controls["captain_username"]);


			if (timeLabelOnPanel != nullptr)
			{
				Console::WriteLine("time detected: " + timeLabelOnPanel->Text);
				//cout << "detected: " << context.marshal_as<std::string>(timeLabelOnPanel->Text) << endl; //flag

				if (timeLabelOnPanel->Text == current_time)
				{
					// remove the panel from the flow layout panel
					//panel->Dispose();
					string c_name = context.marshal_as<std::string>(captain_name->Text);
					fpn_schedule_requests->Controls->Remove(panel);
					in_a_Ride = 1;

					Ride ride;
					ride.Location = context.marshal_as<std::string>(ride_location->Text);
					ride.Distination = context.marshal_as<std::string>(ride_distination->Text);
					ride.captain.user_data.full_name.firstname = c_name.substr(0, c_name.find(' '));
					ride.captain.user_data.full_name.lastname = c_name.substr(c_name.find(' ') + 1, c_name.size() - 1);
					ride.captain.user_data.SUser_name = context.marshal_as<std::string>(c_username->Text);

					cout << ride.captain.user_data.full_name.firstname << "---" << ride.captain.user_data.full_name.lastname << endl;
					Pending_ride = ride;

					


					cout << "flag wanted" << endl;
					pictureBox13->BringToFront();
					//Add_to_rider_pending_list(Pending_ride);
					set_captain_status_message("Your ride has jut started, hope you a great ride, captain!");
					Ride_timer->Start();

					Remove_from_data(ride.Location, ride.Distination, context.marshal_as<std::string>(current_time));

					cout << "panel removed successfully" << endl;



					/*

					*/
				}
			}
			else cout << "nullptr :(" << endl;


		}

	}
	else // rider
	{
		for (int i = 0; i < fpn_rider_schedule_list->Controls->Count; i++)// 2 panels ---> 2 loop times
		{
			Panel^ panel = dynamic_cast<Panel^>(fpn_rider_schedule_list->Controls[i]); // automatically detect panel


			// get the time label on the panel
			//Label^ timeLabelOnPanel = dynamic_cast<Label^>(panel->Controls["timeLabel"]);

			//captain_name

			Label^ timeLabelOnPanel = dynamic_cast<Label^>(panel->Controls["timeLabel"]);
			Label^ captain_name = dynamic_cast<Label^>(panel->Controls["captain_name"]);
			Label^ ride_location = dynamic_cast<Label^>(panel->Controls["ride_location"]);
			Label^ ride_distination = dynamic_cast<Label^>(panel->Controls["ride_distination"]);
			Label^ c_username = dynamic_cast<Label^>(panel->Controls["captain_username"]);


			if (timeLabelOnPanel != nullptr) // for safty :D(make sure it detected a panel)
			{
				Console::WriteLine("time detected: " + timeLabelOnPanel->Text);
				//cout << "detected: " << context.marshal_as<std::string>(timeLabelOnPanel->Text) << endl; //flag

				if (timeLabelOnPanel->Text == current_time) //if clock time == the ride time --> it starts
				{
					// remove the panel from the flow layout panel
					//panel->Dispose();
					string c_name = context.marshal_as<std::string>(captain_name->Text);
					fpn_rider_schedule_list->Controls->Remove(panel);
					in_a_Ride = 1;

					Ride ride;
					ride.Location = context.marshal_as<std::string>(ride_location->Text);
					ride.Distination = context.marshal_as<std::string>(ride_distination->Text);
					ride.captain.user_data.full_name.firstname = c_name.substr(0, c_name.find(' '));
					ride.captain.user_data.full_name.lastname = c_name.substr(c_name.find(' ') + 1, c_name.size() - 1);
					ride.captain.user_data.SUser_name = context.marshal_as<std::string>(c_username->Text);

					ride.rider.user_data.SUser_name = Program_user.user_data.SUser_name;

					cout << ride.captain.user_data.full_name.firstname << "---" << ride.captain.user_data.full_name.lastname << endl;
					Pending_ride = ride;

					cout << "flag wanted" << endl;
					pictureBox19->BringToFront();
					Add_to_rider_pending_list(Pending_ride);
					Remove_scheduled_ride_from_files(ride); ///////
					set_status_message("Your ride with captain " + c_name + " started, hope you a great ride!");
					Ride_timer->Start();

					cout << "panel removed successfully" << endl;



					/*

					*/
				}
			}
			else cout << "nullptr :(" << endl;


		}
	}

	
}



private: System::Void btn_search_Click(System::Object^ sender, System::EventArgs^ e) {
	fpn_riders_around->Controls->Clear();
	button32->PerformClick();
	pn_search_riders->BringToFront();

}

private: System::Void rider_search_timer_Tick(System::Object^ sender, System::EventArgs^ e) {

	cout << "refresh_cnt : " << refresh_cnt << endl;
	if (refresh_cnt >= (1 + rand() % 5))
	{
		refresh_cnt = 0;


		fpn_riders_around->Controls->Clear();
		refresh_anim->Visible = 0;
		Search_riders_around_me();
		search_anim->Visible = 0;
		rider_search_timer->Stop();

		
	}
	else
	{
		refresh_cnt++;
	}
}
private: System::Void pictureBox33_Click(System::Object^ sender, System::EventArgs^ e) {


	label37->Text = "You have no notifications ";
	pictureBox33->Visible = 0;
	pictureBox15->Visible = 0;//notification

}
	//rider_status_panel->Visible = 1;
private: System::Void pictureBox34_Click(System::Object^ sender, System::EventArgs^ e) {

	if (rider_status_panel->Visible == 0) // if hidden
	{
		pictureBox33->Visible = 0;
		pictureBox15->Visible = 0;
		label37->Text = "You have no notifications";
		rider_status_panel->Visible = 1;
	}
	else
	{
		cout << "wanted!" << endl;
		rider_status_panel->Visible = 0;

	}

}


private: System::Void button32_Click(System::Object^ sender, System::EventArgs^ e) {
	search_anim->Visible = 1;
	rider_search_timer->Start();
}
private: System::Void btn_clear_rider_history_Click(System::Object^ sender, System::EventArgs^ e) {

	if(rider_history_rides_count)
	Clear_rider_history();
}

};
}


/*




*/