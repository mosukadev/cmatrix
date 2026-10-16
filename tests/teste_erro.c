#include "teste.h"
#include "teste_erro.h"
#include <libmatriz.h>

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void mtz_mensagem_erro_ok() {
    const char *msg = mtz_mensagem_erro(MTZ_OK);

    VERIFICA(msg != NULL && msg[0] != '\0', "mtz_mensagem_erro_ok");
}

void mtz_mensagens_erros_diferentes() {
    bool sucesso = true;
    
    for (int i = 1; i < MTZ_ITERATOR; i++) {
        if (sucesso == false) break;

        const char *msg1 = mtz_mensagem_erro(i);

        if (msg1 == NULL) {
            sucesso = false;
            break;
        }

        for (int j = i+1; j < MTZ_ITERATOR; j++) {
            const char *msg2 = mtz_mensagem_erro(j);
            
            if (msg2 == NULL) {
                sucesso = false;
                break;
            }

            if(strcmp(msg1, msg2) == 0) {
                sucesso = false;
                break;
            }
        }
    }

    VERIFICA(sucesso, "mtz_mensagens_erros_diferentes");
}

void mtz_codigo_erro_invalido() {
    const char *msg = mtz_mensagem_erro(999);
    
    VERIFICA(msg != NULL, "mtz_codigo_erro_invalido");
}
