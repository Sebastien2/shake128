


void fillStateFromString(int w, char state[5][5][w], char * contenu, int b, int l);

void fillStringFromState(int w, char state[5][5][w], char * contenu, int b, int l);

void fillStringFromStateSection313(int w, char state[5][5][w], char * contenu, int b, int l);

void getLane(int w, char lane[w], int i, int j, char state[5][5][w]);

void getPlane(int j, int w, char plane[5*w], char state[5][5][w]);

void creerStringFromBits(int len1, char * sortie1, int len2, char * sortie2);

void creerBitsFromString(int len, char * entree, char * sortie);

void creerStringFromHexString(int lenEntree, char * entree, char * sortie);
