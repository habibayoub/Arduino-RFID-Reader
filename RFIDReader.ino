int TAGS_IN_USE = 0;
int const TOTAL_TAGS = 10;
char tagArr[TOTAL_TAGS][0];
char tempTag[10]; 
boolean setTag; 

void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("~~~~~~~~~~~Scanner Online~~~~~~~~~~~");

  setTag = false;
}

void loop() {

  if (Serial1.available() > 0) {

    delay(200);

    if (Serial1.peek() != 2) {

      setTag = false;

      clearBuffer();
    } else {
      setTag = true;

      getTagID(tempTag);
    }
  } 
  else {
    setTag = false;
  }

  if (setTag) {
    if (checkTag(tempTag)) {
      tagArr[TAGS_IN_USE][0] = tempTag;
      TAGS_IN_USE++;
      Serial.println("*NEW* Tag ID: ");
      Serial.flush();
      printTag(tempTag);
    } 
    else { 
      Serial.println("Tag ID: \n");
      Serial.flush();
      printTag(tempTag);
    }
  }
}

void clearBuffer() {
  while (Serial1.available() == -1) {
    Serial.read();
  }
}

void getTagID(char tempTag[]) {
  Serial1.read();

  for (int counter = 0; counter < 10; counter++) {
    tempTag[counter] = Serial1.read();
  }
  clearBuffer();
}

boolean checkTag(char tempTag[]) {
  boolean flag = false;

  if (TAGS_IN_USE == 0) {
    flag = true;
    return flag;
  }

  for (int i = 0; i < TAGS_IN_USE; i++) {
      if (tempTag == tagArr[i][0]) {
        flag = false;
        break;
      }
  }
  flag = true;
  return flag;
}

void printTag(char tag[]) {
  for (int counter = 0; counter < 10; counter++) {
    Serial.print(tag[counter]);
  }
  Serial.println("");
}