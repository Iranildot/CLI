#include "tnt.h"

char CHAVE[90];
char CHAVE_REVERSA[90];
int geraChave(void);

int main(void)
{
    // Prepare the CONST variables to recieve the key
    for (int i = '!'; i <= 'z'; i++){
        CHAVE_REVERSA[i - 33] = i;
        CHAVE[i - 33] = i;
    }

    // If the file exits the key stored in there will be read to the variable
    FILE * key = fopen("key.txt", "r");
    if (key == NULL){
        geraChave();
        printf("The file that must contain KEY was not found!");
        return EXIT_FAILURE;
    }
    char leitor;
    int i = 0;

    // Iteration over the file to load KEY
    while ((leitor = fgetc(key)) != EOF)
    {
        CHAVE[i] = leitor;
        i++;
    }

    // Closing the file
    fclose(key);

    // Ask the user what to do
    do {
        string c = grabText("Do you want ENCRYPT (1), DECRYPT (2), SEE KEY (3), CHANGE KEY (4) OR QUIT (5)?");

        if ((c[0] == '5') && (c[1] == '\0')){
            free(c);
            break;
        }

        if ((c[0] == '1' && c[1] == '\0') || (c[0] == '2' && c[1] == '\0')){
            string texto = grabText("TEXT: "); 
            int tamanhoT = strlen(texto);
            int tamanhoC = strlen(CHAVE);

            // Print the encrypted text
            if (c[0] == '1' && c[1] == '\0'){
                printf("ENCRYPTED: ");
                for(int i = 0; i < tamanhoT; i++){
                    for(int j = 0; j < tamanhoC; j++){
                        if (texto[i] == CHAVE_REVERSA[j]){
                            printf("%c", CHAVE[j]);
                            break;
                        }
                        
                        if (j == tamanhoC - 1){
                            printf("%c", texto[i]);
                            break;
                        }
                        
                    }
                }
                
            }
            else{
                // Print the decrypted text
                printf("DECRYPTED: ");
                for(int i = 0; i < tamanhoT; i++){
                    for(int j = 0; j < tamanhoC; j++){
                        if (texto[i] == CHAVE[j]){
                            printf("%c", CHAVE_REVERSA[j]);
                            break;
                        }
                        
                        if (j == tamanhoC - 1){
                            printf("%c", texto[i]);
                            break;
                        }
                    }
                }
            }
            printf("\n");
            free(texto);
        }else if (c[0] == '3' && c[1] == '\0'){
            printf("\n\nKEY: %s\n\n\n", CHAVE);
        }else if (c[0] == '4' && c[1] == '\0'){

            string confirm = grabText("(1) Generate a random KEY\n(2) Type a KEY\nAnswer: ");

            if (strcmp(confirm, "1") == 0)
            {
                printf("\n\nOld KEY: %s\n\n", CHAVE);
                geraChave();
                printf("New KEY: %s\n\n\n", CHAVE);
            }else if (strcmp(confirm, "2") == 0)
            { 
                // Opening file to replace KEY
                key = fopen("key.txt", "w");
                if (key == NULL){
                    geraChave();
                    printf("File that must contain KEY was not found!");
                    return EXIT_FAILURE;
                }

                string newKey = grabText("New KEY: ");
                printf("\n\n");

                // Erros messages
                if (strlen(newKey) != 90)
                {
                    printf("The length of KEY must be 90!\n\n\n");
                }
                else
                {

                    // Checking if there is any repeated character in the KEY 
                    int verified = 0;
                    // Putting KEY into file and into CHAVE variable
                    for (int i = 0; i < 90; i++){
                        verified = 0;
                        for (int j = 0; j < 90; j++){
                            if (newKey[i] == newKey[j])
                            {
                                verified += 1;
                                if (verified > 1)
                                {
                                    break;
                                }
                            }
                        }
                    }

                    if (verified == 1)
                    {
                        for (int i = 0; i < 90; i++){
                            fputc(newKey[i], key);
                            CHAVE[i] = newKey[i];
                        }
                    }
                    else
                    {
                        printf("The key must not have repeated caracters!\n\n\n");
                    }

                }


                // Closing file
                fclose(key);
                free(newKey);

            }
            free(confirm);
        }
        free(c);
    }while(1);

    return EXIT_SUCCESS;
    
}

// Function that generates kyes
int geraChave(void){
    FILE *key = fopen("key.txt", "w");
    if (key == NULL){
        printf("Problems opening the file where is the key!");
        return EXIT_FAILURE;
    }

    int random = 0;
    char aux;
    for (int i = 0; i < 90; i++){
        random = rand() % 90;
        aux = CHAVE[i];
        CHAVE[i] = CHAVE[random];
        CHAVE[random] = aux;
    }

    for (int i = 0; i < 90; i++){
        fputc(CHAVE[i], key);

    }
    fclose(key);

    return EXIT_SUCCESS;
    
}
