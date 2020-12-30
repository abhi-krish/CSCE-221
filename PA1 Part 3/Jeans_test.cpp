#include <iostream>
#include <fstream>
#include <sstream>
#include "Jeans.h"
#include "Collection.h"

using CollectionJN = Collection<Jeans, Jeans_colors, Jeans_sizes>;

istream& operator>>(istream& is, CollectionJN& c) {
  string temp_color;
  string temp_size;
  Jeans_colors color;
  Jeans_sizes size;

  while (is >> temp_color >> temp_size) {
  if (temp_color == "white")  {
    color = Jeans_colors::white;
  }
  else if (temp_color == "blue")  {
    color = Jeans_colors::blue;
  }
  else if (temp_color == "grey") {
    color = Jeans_colors::grey;
  }
  else if (temp_color == "black") {
    color = Jeans_colors::black;
  }

  if (temp_size == "small") {
    size = Jeans_sizes::small;
  }
  else if (temp_size == "medium") {
    size = Jeans_sizes::medium;
  }
  else if (temp_size == "large")  {
    size = Jeans_sizes::large;
  }
  else if (temp_size == "xlarge") {
    size = Jeans_sizes::xlarge;
  }
  Jeans temp_Jeans(color, size);
  c.insert_item(temp_Jeans);
  }
  return is;
}

void test_jeans(){
        Jeans jeans_1 = Jeans(Jeans_colors::grey, Jeans_sizes::small);
        Jeans jeans_2 = Jeans(Jeans_colors::grey, Jeans_sizes::large);
        Jeans jeans_3 = Jeans(Jeans_colors::blue, Jeans_sizes::large);
        // Jeans jeans_4 = Jeans(Jeans_colors::black, Jeans_sizes::medium);
        CollectionJN collection_0;
        CollectionJN collection_1;
        CollectionJN collection_2(3);
        CollectionJN collection_3(5);
        CollectionJN collection_file(1);
        collection_0.insert_item(jeans_1);
        collection_0.make_empty();
        collection_1.insert_item(jeans_1);
        collection_2.insert_item(jeans_2);
        
        collection_2.print_items();
        collection_2.insert_item(Jeans(Jeans_colors::blue, Jeans_sizes::small));
        collection_2.insert_item(jeans_3);
        collection_2.insert_item(jeans_3);
        CollectionJN collection_copy(collection_1);
        collection_1.insert_item(Jeans(Jeans_colors::black, Jeans_sizes::small));
        CollectionJN collection_7 = move(collection_1);
        collection_2.insert_item(Jeans(Jeans_colors::blue, Jeans_sizes::medium));
        collection_2.insert_item(Jeans(Jeans_colors::grey, Jeans_sizes::large));
        collection_2.insert_item(Jeans(Jeans_colors::grey, Jeans_sizes::large));
        collection_2.remove_this_item(jeans_2);
        
        collection_2.print_items();
        collection_copy.make_empty();
        if(collection_2.is_empty()){
            collection_2.insert_item(Jeans(Jeans_colors::black, Jeans_sizes::small));
        }
        ifstream ifs("jeans1.data");
        ifs >> collection_file;
        collection_file.insert_item(jeans_3);
        collection_file.insert_item(jeans_3);
        collection_2.insert_item(jeans_3);
        collection_2.insert_item(jeans_3);
        collection_2.insert_item(jeans_2);
        collection_2.insert_item(jeans_1);
        
        collection_file.print_items();
      
                    swap(collection_file,collection_2);
                    collection_3 = make_union(collection_file,collection_2);                
                     if((collection_3.total_items() - collection_2.total_items()) == collection_file.total_items()){
                          sort_by_size(collection_2,Sort_choice::selection_sort);
                          cout<<collection_3;
                     }
}
