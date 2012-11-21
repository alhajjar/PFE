#include <iostream>
#include <fstream>      
#include <vector>
#include <string>
#include <algorithm>   
#include <iterator>     
#include <vector>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/trim.hpp>


int name_address_sport_parser()
{
    using namespace std;
    using namespace boost;
    using std::vector;
    string data("/home/alhajjar/Bureau/pfe/Simulations_diffaphids/Data/donnees_temp_min_2000_2011_1.csv");

    ifstream in(data.c_str());
    if (!in.is_open()) return 1;

    typedef tokenizer< escaped_list_separator<char> > Tokenizer;

    escaped_list_separator<char> sep('\\',';', '\"');

    vector< string > vec;
    vector < string > * recup = NULL;
    vector<string>::iterator it;
    vector< vector<string> > vI2Matrix;
    vector< vector<string> >::iterator iter_ii;
    vector< string>::iterator iter_jj;

    string line;
    string buffer;

    bool inside_quotes(false);
    size_t last_quote(0);

    while (getline(in,buffer))
    {
        // --- deal with line breaks in quoted strings

        last_quote = buffer.find_first_of('"');


            while (last_quote != string::npos)
        {
            if (buffer[ last_quote - 1 ] != '\\'){
            inside_quotes = !inside_quotes;
            }
            last_quote = buffer.find_first_of('"',last_quote+1);
        }

        line.append(buffer);

        if (inside_quotes){
            line.append("\n");
            continue;
        }

        Tokenizer tok(line, sep);

        vec.assign(tok.begin(),tok.end());

    if (recup == NULL)
      recup = new vector<string> (vec.size());


        line.clear(); // clear here, next check could fail

//on faist un parse 3 elements par 3
    /*    if (vec.size() < 3) continue;

        copy(vec.begin(), vec.end(),ostream_iterator<string>(cout, "\n"));

        cout << "\n----------------------" << endl;*/
      //  if (vec.size() < 3) continue;
  for ( it=vec.begin() ; it < vec.end(); it++ ){
    //cout << "   " << *it;
    //vec.push_back(*it);
    }
    vI2Matrix.push_back(vec);
    // pas besoin
/*for(iter_ii=vI2Matrix.begin(); iter_ii!=vI2Matrix.end(); iter_ii++)

   {

      for(iter_jj=(*iter_ii).begin(); iter_jj!=(*iter_ii).end(); iter_jj++)

      {

         cout << *iter_jj<<"\t";

      }
cout << "\n----------------------" << endl;
   }*/


   // s'il ya des espace entre les nombres ou les parsers on les enleves
   trim(vec[0]);
trim(vec[1]);
 /* for (unsigned i=0; i<vec.size(); i++){
    cout << "\n " << vec.at(i);
    }*/

    }


    in.close();

    return 0;
}

int main()
{
    name_address_sport_parser();
}
