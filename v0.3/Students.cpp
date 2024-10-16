#include "Mylib.h"
#include "Stud.h"
#include "Util.h"

int main()
{
    //All variables inside main()
    vector<Stud> Students,              //-Vector for storing students data.
                 Students_Under,        //-Vector for storing students data with final result Under 5.
                 Students_Over;         //-Vector for storing students data with final result 5 and Over.
    list<Stud>  Students_list,          //-
                Under_list,             //-
                Over_list;              //-
    Stud        Temp_stud;              //-Temporary value for storing student data.
    string      main_input,             //-User command.
                key,                    //-Key for sorting functions.
                filename;               //-Name of a file to read.
    int number_of_students;             //-Number of students in case of manual input.
    selection print_by;                 //-Result values to print.
    vector<File_info> files;            //-Files data {Name, Size} to create.
    vector<string> testFiles;           //-File names to test.
    stringstream info;
    container_types container_type = container_types::Vector;
    update_info(info, container_type);
    cout << info.str();

    //Choosing function
    while (true) {
        //Input
        cout << "Input function << ";
        cin >> main_input;
        //transforming to lower case for small user input mistakes
        transform(main_input.begin(), main_input.end(), main_input.begin(), ::tolower);

        //Test case
        if (main_input.substr(0, 3) == "tes") {
            print_by = print_selection();
            key = sort_selection(print_by);
            file_selection(testFiles);  //Selecting file names for testing
            test_multiple_files(testFiles, print_by, key);  //Testing
            cout << "Results are in files: 'Stiprus.txt' & 'Silpni.txt'.\n" << endl;
            continue;
        }
        else if (main_input.substr(0, 3) == "cha") {
            (container_type == container_types::Vector) ?
                container_type = container_types::List :
                container_type = container_types::Vector;
            update_info(info, container_type);
            get_type(container_type);
        }
        //Case of reading existing file
        else if (main_input.substr(0, 3) == "ope") {
            print_by = print_selection();
            key = sort_selection(print_by);
            cout << "Select file from this list:\n";
            system("dir  *.txt /B"); //Printing list for choosing .txt file
            while (true) {
                //input
                cout << "\nInput name << ";
                cin >> filename;
                if (filename.substr(filename.length() - 4, 4) != ".txt") filename += ".txt";
                //Opening file for testing
                ifstream file;
                try {
                    file.open(filename);
                    if (!file) {
                        throw runtime_error("File not found!");
                    }
                    break;
                }
                catch (const exception& e) {
                    cerr << e.what() << endl;
                }
            }
            printf("Reading %s\n", filename);
            Input_from_file(Students, filename);    //Reading the file
            printf("Sorting %s\n", filename);
            sort_students(Students, key);           //Sorting data by users choosen key
            sort_to_categories(Students, Students_Under, Students_Over);    //Spliting data to categories
            printf("Printing %s\n", filename);
            output_to_file(Students_Over, filename, print_by);         //Outputing to files
            output_to_file(Students_Under, filename, print_by);         //Outputing to files
            string name_front = filename.substr(0, filename.size() - 4);
            cout << "Results are in files: '" << name_front + "_stiprus.txt' & '" << name_front + "_silpni.txt'." << endl;
            continue;
        }
        //Ending programs work
        else if (main_input.substr(0, 3) == "end") {
            system("pause");
            return 1;
        }
        //Printing the list of functions
        else if (main_input.substr(0, 3) == "inf") {
            cout << info.str();
            continue;
        }
        //Printing list of available .txt files
        else if (main_input.substr(0, 3) == "sho") {
            cout << "\nAvailable '.txt' files:\n";
            system("dir *.txt /B");
            continue;
        }
        //Creating of test data files
        else if (main_input.substr(0, 3) == "cre") {
            create_file_selection(files);
            create_multiple_files(files);
            continue;
        }
        //Cases for manual input and bad inputs
        else {
            try {
                number_of_students = stoi(main_input);
            }
            catch (const exception&) {
                cout << "Unknown command! Please try again.\n";
                continue;
            }
            //Key and result values selection
            print_by = print_selection();
            key = sort_selection(print_by);
            //Manual input
            Students.reserve(number_of_students);
            for (int i = 0; i < number_of_students; i++) {
                input(Temp_stud);
                Students.push_back(Temp_stud);
                clean(Temp_stud);
            }
            sort_students(Students, key);   //Sorting data by users choosen key
            sort_to_categories(Students, Students_Under, Students_Over);    //Spliting data to categories
            output_to_file(Students_Over, "Stiprus.txt", print_by);         //Outputing to files
            output_to_file(Students_Under, "Silpni.txt", print_by);         //Outputing to files
            cout << "Results are in files: 'Stiprus.txt' & 'Silpni.txt'." << endl;
            continue;
        }
    }

}