#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void phase_6 (input) {

  int idx2, var1, var2, var3, idx, var4, var5, var6;
  int storage[6];
  int nodes[6];

  sscanf(input, "%d %d %d %d %d %d", storage[0], storage[1], storage[2],
    storage[3], storage[4], storage[5]);

  idx = 0;
  var3 = storage[0];
  idx2 = 0;

  // Checks if no number is the same and if every number is under 7.
  while(true) {
    var1 = var3;
    var2 = var3;
    var2 -= 1;

    if(var2 > 5) {
      explode_bomb();
    }

    idx2 += 1;
    if (idx2 == 6) {
      idx = 0;
      break;
    }

    var5 = idx2;
    do{
      var2 = storage[var2];

      if(var2 == var1) {
        explode_bomb();
      }

      var5 += 1;
    }while(var5 <= 5);

    var3 = *(&var3 + 4);
  }

  //save the addresses - 8 of the 6 nodes in nodes
  do{
    var4 = storage[rsi];

    if(var4 <= 1) {
      var6 = 0x6042f0;
    }
    else {
      var2 = 1;
      var6 = 0x6042f0; 

      //add n * 8 to every address
      do{
        var6 = var6 + 8;
        var2 += 1;
      }while(var2 != var4);
    }

    nodes[idx] = var6;
    idx += 1;
  }while(idx != 6);

  var5 = nodes[0];
  var2 = nodes[1];
  idx = storage[0];
  var4 = nodes[0];

  //increase the addresses at index 1-5 in nodes by 8
  while (true){
    var6 = &var2;

    //*(&var4+8) = next index in nodes
    *(&var4 + 8) = var6;
    &var2 += 8;

    //makes this loop execute 6 times
    if(var2 == &idx){
      break;
    }
    var4 = var6;
  }

  *(var6+8) = 0;
  
  // If value at next node in order is larger than the previous, explode
  var1 = 5;
  do {
    va2r2 = nodes[6-var1];
    if (var2 <= var5) {
      explode_bomb();
    }
    var5 = nodes[6-var1];
    var2 -= 1;
  }while(var2 != 0);
}