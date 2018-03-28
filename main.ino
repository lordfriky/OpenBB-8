/*
  OpenBB-8 PoC code
  Open source BB-8 project
  
  Project made by:
  - Alain Flores Temblador
  - Carlos Alberto R. de León Quezada
  - Daniel Hernández Muñoz
  - Oscar Jesús de la Torre Martínez
  
  This project was published under the GNU General Public License 3.0
  More info in https://github.com/lordfriky/OpenBB-8/blob/master/LICENSE
*/

char dataIn='S';      // Declaration of bluetooth variables
char determinant;     // We just need one, but TechBuilder made it like this
char det;

int vel = 250;        // Initial speed

void setup(){
  Serial.begin(9600);
                        //Declaration of both motors
  pinMode(5, OUTPUT);     //Left motor
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);     //Right motor
  pinMode(10, OUTPUT);

}

void loop(){
  det = check();
  
/*  
  Anatomy of the movement function:
  There's 2 motors, left (5 & 6) and right (9 & 10)
  The first 2 'analogWrite' belogs to left motor, the next ones to the right
  The first line of both motors belongs to the front, the next ones to the back
  So if we set both of the first lines of the motors the BB-8 is going to move to the front
  And vice versa
  If we divide the 'vel' value we can move the BB-8 in a diagonal
  
  And that's all the basic info you need to know to understant the code
*/
  
  while (det == 'F'){   // F, forward
    analogWrite(5, vel);
    analogWrite(6, 0);
    analogWrite(9, vel);
    analogWrite(10, 0);
    
    det = check();
  }
  
  while (det == 'B'){   // B, back
    analogWrite(5, 0);
    analogWrite(6, vel);
    analogWrite(9, 0);
    analogWrite(10, vel);
    
    det = check();
  }

  while (det == 'L'){   // L, left rotation
    analogWrite(5, 0);
    analogWrite(6, vel);
    analogWrite(9, vel);
    analogWrite(10, 0);
    
    det = check();
  }
  
  while (det == 'R'){   // R, right rotation
    analogWrite(5, vel);
    analogWrite(6, 0);
    analogWrite(9, 0);
    analogWrite(10, vel);
    
    det = check();
  }
  
  while (det == 'I'){   // I, northeast
    analogWrite(5, vel);
    analogWrite(6, 0);
    analogWrite(9, vel/2);
    analogWrite(10, 0);
    
    det = check();
  }
  
  while (det == 'J'){   // J, southeast
    analogWrite(5, 0);
    analogWrite(6, vel);
    analogWrite(9, 0);
    analogWrite(10, vel/2);
    
    det = check();
  }  
  
  while (det == 'G'){   // G, northwest
    analogWrite(5, vel/2);
    analogWrite(6, 0);
    analogWrite(9, vel);
    analogWrite(10, 0);
    
    det = check();
  }
  
  while (det == 'H'){   // H, southwest
    analogWrite(5, 0);
    analogWrite(6, vel/2);
    analogWrite(9, 0);
    analogWrite(10, vel);
    
    det = check();
  }  
  
  while (det == 'S'){   // S, stop
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(9, 0);
    analogWrite(10, 0);
    
    det = check();
  }
}

int check(){                  // Bluetooth read function (not really needed, btw...)
  if (Serial.available() > 0){// I'm just following the TechBuilder code
    dataIn = Serial.read(); 
    
    //-------- DIRECTION --------//
    
    if (dataIn == 'F'){
      determinant = 'F';      // Forward
    } 
    else if (dataIn == 'B'){
      determinant = 'B';      // Back
    }
    else if (dataIn == 'L'){
      determinant = 'L';      // Left Rotation
    }
    else if (dataIn == 'R'){
      determinant = 'R';      // Right Rotation
    }
    else if (dataIn == 'I'){
      determinant = 'I';      // Northeast
    } 
    else if (dataIn == 'J'){
      determinant = 'J';      // Southeast
    }
    else if (dataIn == 'G'){
      determinant = 'G';      // Northwest
    }   
    else if (dataIn == 'H'){
      determinant = 'H';      // Southwest
      
    }
    else if (dataIn == 'S'){
      determinant = 'S';      // Stop
    }
    
    //---------- SPEED ----------//
    
    else if (dataIn == '0'){
      vel = 250;              // Max Speed
    }
    else if (dataIn == '1'){
      vel = 174;              // Mid Speed
    }
    else if (dataIn == '2'){
      vel = 86;               // Min Speed
    }
  }
  return determinant;         // Set check() value as  determinant
}
