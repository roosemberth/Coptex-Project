#!/usr/bin/env nodejs

var initial_family = [2,3,5];
var required_prime_numbers = 1000000;

var is_num_div_by_brothers = function(num, brothers){
     if (brothers.length != undefined) {var family_size = brothers.length;}
     else {brothers = initial_family; var family_size = initial_family.length;}
     var was_divisable = 0;
     for(i=0; i<=family_size; ++i) {
          if ((Math.round(num/brothers[i])-(num/brothers[i]))==0) {was_divisable = 1; break;}
     }
     return was_divisable;
}


var get_prime_numbers = function(required_amount, seed_family){
     console.log("Calculating Prime Numbers\n\n");
     var prime_numbers = seed_family;
     var found_numbers = prime_numbers.length;
     var is_guess_divisible = 0
     for (num=2; found_numbers<=required_amount; ++num){
          is_guess_divisible = is_num_div_by_brothers(num, prime_numbers); 
          if (is_guess_divisible==0) {prime_numbers.push(num);found_numbers++; console.log("\r \b" + found_numbers + " Prime Numbers Found");}
     }
     return prime_numbers;
}

prime_numbers = get_prime_numbers(required_prime_numbers, initial_family);
console.log("The First " + required_prime_numbers + " Prime Numbers are: \n\n" + prime_numbers.join(","));

var fs = require('fs');
fs.writeFileSync("The first " + required_prime_numbers + " Prime Numbers.txt", prime_numbers.join(","));
console.log("\na file with the first " + required_prime_numbers + " prime numbers has been created! \nFilename: " + '"' + "The first " + required_prime_numbers + " Prime Numbers.txt" + '"' + "\n");
