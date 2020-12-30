#include <iostream>
#include <fstream>
#include <sstream>
#include "Stress_ball.h"
#include "Collection.h"

using CollectionSB = Collection<Stress_ball, Stress_ball_colors, Stress_ball_sizes>;

istream& operator>>(istream& is, CollectionSB& c) {
  string temp_color;
  string temp_size;
  Stress_ball_colors color;
  Stress_ball_sizes size;

  while (is >> temp_color >> temp_size) {
      if (temp_color == "red")  {
        color = Stress_ball_colors::red;
      }
      else if (temp_color == "blue")  {
        color = Stress_ball_colors::blue;
      }
      else if (temp_color == "yellow")  {
        color = Stress_ball_colors::yellow;
      }
      else if (temp_color == "green") {
        color = Stress_ball_colors::green;
      }
      if (temp_size == "small") {
        size = Stress_ball_sizes::small;
      }
      else if (temp_size == "medium") {
        size = Stress_ball_sizes::medium;
      }
      else if (temp_size == "large")  {
        size = Stress_ball_sizes::large;
      }
      Stress_ball temp_stress_ball(color, size);
      c.insert_item(temp_stress_ball);
  }
  return is;
}
void test_stress_balls(){
        Stress_ball stress_ball_1 = Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::large);
        Stress_ball stress_ball_2 = Stress_ball(Stress_ball_colors::yellow, Stress_ball_sizes::large);
        Stress_ball stress_ball_3 = Stress_ball(Stress_ball_colors::green, Stress_ball_sizes::small);
        Stress_ball stress_ball_4 = Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::medium);
        CollectionSB collection_1;
        CollectionSB collection_2(3);
        CollectionSB collection_3(5);
        CollectionSB collection_file(1);
        collection_2.insert_item(stress_ball_2);
        collection_2.insert_item(stress_ball_4);
        collection_1.insert_item(stress_ball_1);
        collection_2.insert_item(stress_ball_2);
        collection_2.insert_item(Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::small));
        collection_2.insert_item(stress_ball_3);
        collection_2.insert_item(stress_ball_3);
        CollectionSB collection_4 = collection_1;
        CollectionSB collection_5(move(collection_4));
        collection_1.insert_item(Stress_ball(Stress_ball_colors::green, Stress_ball_sizes::small));
        collection_2.insert_item(Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::medium));
        collection_2.insert_item(Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::large));
        collection_2.insert_item(Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::large));
        collection_2.remove_this_item(stress_ball_2);        
        collection_2.print_items();
        ifstream ifs("stress_ball1.data");
        ifs >> collection_file;
        collection_file.insert_item(stress_ball_3);
        collection_file.insert_item(stress_ball_3);
        collection_2.insert_item(stress_ball_3);
        collection_2.insert_item(stress_ball_3);
        collection_2.insert_item(stress_ball_2);
        collection_2.insert_item(stress_ball_1);
        
        collection_file.print_items();
        collection_3 = make_union(collection_file,collection_2);
        if(collection_3.total_items() == (collection_file.total_items() + collection_2.total_items())){ 
                          sort_by_size(collection_2,Sort_choice::insertion_sort);                           
                          cout<<collection_3;
        }
}

