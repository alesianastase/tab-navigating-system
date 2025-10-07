/* NĂSTASE Alesia-Raluca - 312CC */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct page {
    int id;
    char url[50];
    char *description;
} page;

typedef struct stackLink {
    page *pag;
    struct stackLink *next;
} stackLink;

typedef struct stack {
    stackLink *head; //o sa fie top of the stack
} stack;

typedef struct tab {
    int id;
    page *currentPage;
    stack *backwardStack;
    stack *forwardStack;
} tab;

typedef struct tabLink {
    tab *t;
    struct tabLink *prev, *next;
} tabLink;

typedef struct tabsList {
    tabLink *santi;
} tabsList;

typedef struct browser {
    tab *current;
    tabsList list;
} browser;

page *create_pag_imp()
{
    page *pagImp = (page *)malloc(sizeof(page));
    int l;

    if (pagImp == NULL) {
        exit(0);
    }

    pagImp->id = 0;
    strcpy(pagImp->url, "https://acs.pub.ro/");
    pagImp->description = (char *)malloc(18 * sizeof(char));

    if (pagImp->description == NULL) {
        exit(0);
    }

    strcpy(pagImp->description, "Computer Science");
    l = strlen(pagImp->description);
    pagImp->description[l] = '\n';
    pagImp->description[l + 1] = '\0';

    return pagImp;
}

void create_tab_zero(tabLink **santi)
{
    tabLink *newLink = (tabLink *)malloc(sizeof(tabLink));
    newLink->t = (tab *)malloc(sizeof(tab));

    if (newLink == NULL || newLink->t == NULL) {
        exit(0);
    }

    newLink->t->id = 0;
    newLink->t->currentPage = create_pag_imp();
    newLink->t->backwardStack = (stack *)malloc(sizeof(stack));
    newLink->t->forwardStack = (stack *)malloc(sizeof(stack));

    if (newLink->t->backwardStack == NULL || newLink->t->forwardStack == NULL) {
        exit(0);
    }

    newLink->t->backwardStack->head = NULL;
    newLink->t->forwardStack->head = NULL;
    newLink->next = *santi;
    newLink->prev = *santi;
    (*santi)->next = newLink;
    (*santi)->prev = newLink;
}

tabLink *create_santi()
{
    tabLink *santi = (tabLink *)malloc(sizeof(tabLink));

    if (santi == NULL) {
        exit(0);
    }

    santi->next = santi->prev = santi;
    santi->t = NULL;
    return santi;
}

void new_tab(browser *b, int tid)
{
    tabLink *newLink = (tabLink *)malloc(sizeof(tabLink));
    newLink->t = (tab *)malloc(sizeof(tab));

    if (newLink == NULL || newLink->t == NULL) {
        exit(0);
    }

    newLink->t->id = tid;
    newLink->t->currentPage = create_pag_imp();
    newLink->t->backwardStack = (stack *)malloc(sizeof(stack));
    newLink->t->forwardStack = (stack *)malloc(sizeof(stack));

    if (newLink->t->backwardStack == NULL || newLink->t->forwardStack == NULL) {
        exit(0);
    }

    newLink->t->backwardStack->head = NULL;
    newLink->t->forwardStack->head = NULL;

    newLink->prev = b->list.santi->prev;
    newLink->next = b->list.santi;
    b->list.santi->prev->next = newLink;
    b->list.santi->prev = newLink;
    b->current = newLink->t;
}

void free_stack(stack *s)
{
    stackLink *temp = s->head;
    stackLink *aux;

    while (temp != NULL) {
        aux = temp;
        temp = temp->next;
        free(aux->pag->description);
        free(aux->pag);
        free(aux);
    }

    free(s);
}

void close(browser *b, FILE *out)
{

    tabLink *curr = b->list.santi->next->next; // tab 1
    //incep de la tab 1, pt ca 0 nu poate sa fie sters

    if (b->current->id == 0) {
        fprintf(out, "403 Forbidden\n");
        return;
    }

    while (curr->next != b->list.santi && curr->t != b->current) {
        curr = curr->next;
    }

    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    b->current = curr->prev->t;

    free(curr->t->currentPage->description);
    free(curr->t->currentPage);
    free_stack(curr->t->backwardStack);
    free_stack(curr->t->forwardStack);
    free(curr->t);
    free(curr);
}

void open_id(browser *b, int id, FILE *out)
{
    tabLink *temp = b->list.santi->next; // tab 0

    while (temp->next != b->list.santi && temp->t->id != id) {
        temp = temp->next;
    }
    /*parcurg pana gasesc un tab care are id-ul specificat
    sau ajung la ultimul tab*/

    if (temp->next==b->list.santi && temp->t->id != id) {
        fprintf(out, "403 Forbidden\n");
        return;
    }
    /*daca a ajuns la ultimul tab si id-ul tot
    difera, atunci nu exista tab-ul cautat*/
    
    b->current = temp->t;
}

void next(browser *b)
{
    tabLink *temp = b->list.santi->next; // tab 0

    while (temp->next != b->list.santi && temp->t->id != b->current->id) {
        temp = temp->next;
    }
    /*parcurg pana ajung la ultimul element sau pana intalnesc tab-ul
    cu id-ul tab-ului curent*/

    if (temp->next == b->list.santi) {
        temp = temp->next;
    }
    /*daca e ultimul tab, trebuie sa ajung la santinela pentru ca urmatorul
    temp->next sa indice tab 0*/

    temp = temp->next; // tab-ul urmator dupa tab curent
    b->current = temp->t;
}

void prev(browser *b)
{
    tabLink *temp = b->list.santi->next; // tab 0

    while (temp->next != b->list.santi && temp->next->t->id != b->current->id) {
        temp = temp->next;
    }
    /*parcurg pana ajung la ultimul element sau pana cand tab-ul urmator
    are id-ul dorit (temp o sa fie tab-ul din stanga celui curent)*/

    b->current = temp->t;
}

void page_id(browser *b, page *pag, int m, int id, FILE *out)
{
    int i, found = 0;
    stackLink *newPageLink;
    page *newPage;

    for (i = 1; i <= m; i++) {
        if (pag[i].id == id) {
            newPage = (page *)malloc(sizeof(page));
            if (newPage == NULL) {
                exit(0);
            }
            newPage->description = (char *)malloc((strlen(pag[i].description) + 1) * sizeof(char));
            if (newPage->description == NULL) {
                exit(0);
            }
            strcpy(newPage->description, pag[i].description);
            newPage->id = id;
            strcpy(newPage->url, pag[i].url);
            //creez o copie o a paginii
            found = 1;
            break;
        }
    }

    if (found == 0) {
        fprintf(out, "403 Forbidden");
        return;
    }

    newPageLink = (stackLink *)malloc(sizeof(stackLink));
    //am alocat memorie aici pentru a preveni leak-uri, in caz ca found==0
    if (newPageLink == NULL) {
        exit(0);
    }
    newPageLink->pag = b->current->currentPage;
    newPageLink->next = NULL;
    //link-ul ce va fi adaugat in backward stack

    if (b->current->backwardStack->head == NULL) {
        b->current->backwardStack->head = newPageLink;
    } else {
        newPageLink->next = b->current->backwardStack->head;
        b->current->backwardStack->head = newPageLink;
    }

    while (b->current->forwardStack->head != NULL) {
        stackLink *temp = b->current->forwardStack->head;
        b->current->forwardStack->head = b->current->forwardStack->head->next;
        free(temp->pag->description);
        free(temp->pag);
        free(temp);
    }
    //golesc stiva forward

    b->current->currentPage = newPage;
}

void backward(browser *b, FILE *out)
{
    page *currPage = b->current->currentPage; //initiala pagina curenta

    if (b->current->backwardStack->head == NULL) {
        fprintf(out, "403 Forbidden\n");
        return;
    }

    stackLink *temp = b->current->backwardStack->head;
    b->current->backwardStack->head = b->current->backwardStack->head->next;
    b->current->currentPage = temp->pag;
    free(temp);
    /*accesez ultima pagina adaugata in stiva backward (head), o scot din
    stiva si o fac pagina curenta*/

    stackLink *fwdLink = (stackLink *)malloc(sizeof(stackLink));
    if (fwdLink == NULL) {
        exit(0);
    }
    fwdLink->pag = currPage;
    fwdLink->next = NULL;
    //creez un link pentru initiala pagina curenta si o adaug in stiva forward

    if (b->current->forwardStack->head == NULL) {
        b->current->forwardStack->head = fwdLink;
    } else {
        fwdLink->next = b->current->forwardStack->head;
        b->current->forwardStack->head = fwdLink;
    }
}

void forward(browser *b, FILE *out)
{
    stackLink *newPageLink;

    if (b->current->forwardStack->head == NULL) {
        fprintf(out, "403 Forbidden\n");
        return;
    }

    newPageLink = (stackLink *)malloc(sizeof(stackLink));
    if (newPageLink == NULL) {
        exit(0);
    }
    newPageLink->pag = b->current->currentPage;
    newPageLink->next = NULL;
    //pagina curenta

    if (b->current->backwardStack->head == NULL) {
        b->current->backwardStack->head = newPageLink;
    } else {
        newPageLink->next = b->current->backwardStack->head;
        b->current->backwardStack->head = newPageLink;
    }
    //o adaug in stiva backward

    stackLink *temp = b->current->forwardStack->head;
    b->current->currentPage = b->current->forwardStack->head->pag;
    b->current->forwardStack->head = b->current->forwardStack->head->next;
    //scot ultima pag din stiva forward (head) si o fac pag curenta 

    free(temp);
}

void recursive_print(stackLink *head, FILE *out)
{
    if (head == NULL) {
        return;
    }

    recursive_print(head->next, out);
    fprintf(out, "%s\n", head->pag->url);
}

void print_history_id(browser *b, int id, FILE *out)
{
    tabLink *temp = b->list.santi->next;
    stackLink *aux;
    int found = 0;

    while (temp != b->list.santi) {
        if (temp->t->id == id) {
            found = 1;
            break;
        }
        temp = temp->next;
    }
    //caut tab-ul cu id-ul dorit

    if (found == 0) {
        fprintf(out, "403 Forbidden\n");
        return;
    }

    recursive_print(temp->t->forwardStack->head, out);
    //printez incepand cu primul elem din stiva
    fprintf(out, "%s\n", temp->t->currentPage->url);

    aux = temp->t->backwardStack->head;

    while (aux != NULL) {
        fprintf(out, "%s\n", aux->pag->url);
        aux = aux->next;
    }
}

void print(browser *b, FILE *out)
{
    tabLink *temp = b->list.santi->next;
    tabLink *aux;

    while (temp->next != b->list.santi && temp->t != b->current) {
        temp = temp->next;
    }
    //parcurg pana la tab-ul curent

    fprintf(out, "%d", temp->t->id); //id tab curent
    aux = temp->next;

    while (aux != temp) {
        if (aux == b->list.santi) { // daca e santi, trec la id 0 pt ca am tab NULL
            aux = aux->next;
            continue;
        }
        fprintf(out, " %d", aux->t->id);
        aux = aux->next;
    }

    fprintf(out, "\n%s", b->current->currentPage->description);
}

int main()
{

    browser b;
    page *pag;
    tabLink *temp, *aux;
    int n, m, i, tid = 1; //tid=tab id
    char *desc, *s;
    FILE *f = fopen("tema1.in", "r");
    FILE *out = fopen("tema1.out", "w");
    pag = (page *)malloc(50 * sizeof(page));
    s = (char *)malloc(256 * sizeof(char));
    if (pag == NULL || s == NULL) {
        exit(0);
    }
        
    b.list.santi = create_santi();
    create_tab_zero(&b.list.santi);
    b.current = b.list.santi->next->t; // tab zero e tab curent

    fscanf(f, "%d\n", &m);

    for (i = 1; i <= m; i++) {
        fscanf(f, "%d\n", &pag[i].id);
        fgets(pag[i].url, 50, f);
        pag[i].url[strlen(pag[i].url) - 1] = '\0';
        desc = (char *)malloc(256 * sizeof(char));
        if (desc == NULL) {
            exit(0);
        }
        fgets(desc, 256, f);
        pag[i].description = (char *)malloc((strlen(desc) + 2) * sizeof(char));
        // strlen(desc)+2 pt newline-ul de la fgets si terminator de sir
        if (pag[i].description == NULL) {
            exit(0);
        }
        strcpy(pag[i].description, desc);
        free(desc);
    }

    fscanf(f, "%d\n", &n);

    for (i = 0; i < n; i++) {
        fgets(s, 256, f);

        if (s[strlen(s) - 1] == '\n') {
            s[strlen(s) - 1] = '\0';
        }

        if (strcmp(s, "NEW_TAB") == 0) {
            new_tab(&b, tid);
            tid++;
        } else if (strcmp(s, "CLOSE") == 0) {
            close(&b, out);
        } else if (strstr(s, "OPEN") != 0) {
            open_id(&b, atoi(s + 5), out);
        } else if (strcmp(s, "NEXT") == 0) {
            next(&b);
        } else if (strcmp(s, "PREV") == 0) {
            prev(&b);
        } else if (strstr(s, "PAGE") != 0) {
            page_id(&b, pag, m, atoi(s + 5), out);
        } else if (strcmp(s, "PRINT") == 0) {
            print(&b, out);
        } else if (strcmp(s, "BACKWARD") == 0) {
            backward(&b, out);
        } else if (strstr(s, "FORWARD") != 0) {
            forward(&b, out);
        } else if (strstr(s, "PRINT_HISTORY") != 0) {
            print_history_id(&b, atoi(s + 14), out);
        }
    }

    for (i = 1; i <= m; i++) {
        free(pag[i].description);
    }

    free(pag);

    temp = b.list.santi->next;

    while (temp != b.list.santi) {
        aux = temp;
        temp = temp->next;
        free_stack(aux->t->backwardStack);
        free_stack(aux->t->forwardStack);
        free(aux->t->currentPage->description);
        free(aux->t->currentPage);
        free(aux->t);
        free(aux);
    }

    free(b.list.santi);
    free(s);

    fclose(f);
    fclose(out);
}