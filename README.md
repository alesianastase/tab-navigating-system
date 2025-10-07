# tab-navigating-system
Am implementat un sistem de gestionare a istoricului unui
browser. 

DEFINIRE STRUCTURI:
    Am ales sa implementez o structura "tabLink", care e folosita
    pentru navigarea intre  tab-urile din lista dublu inlantuita de tip
    "tabsList". Santinela (santi) face conexiunea dintre tabsList si tabLink.

    De asemenea, am facut ceva similar si pentru stive, unde head o sa fie
    ultimul element introdus in stiva (LIFO). Structura de tip "stackLink"
    permite navigarea intre paginile din stive.

FUNCTII:
    -> CREATE_PAG_IMP: Creeaza pagina implicita.
    -> CREATE_TAB_ZERO: Creeaza tab-ul zero si face conexiunea cu santinela.
    -> CREATE_SANTI: Creeaza santinela.
    -> NEW_TAB: Creeaza un nou tab, alocandu-i memorie. Id-ul este calculat in
        main, crescand de fiecare data cand se apeleaza functia new_tab.
        Pagina curenta o sa fie pagina implicita, care este creata in functia
        create_page_imp.
    -> FREE_STACK: Elibereaza memoria alocata dinamic pentru elementele
        din stiva si pentru stiva in sine.
    -> CLOSE: Am parcurs incepand cu tab-ul 1, deoarece tab-ul 0 nu poate
        sa fie sters niciodata (conditia de eroare). Am refacut link-urile
        din lista si am eliberat memoria pentru tab-ul curent pentru a il
        elimina.
    -> OPEN_ID: Caut tab-ul cu ID-ul specificat prin parcurgerea listei.
        Afisez mesaj de eroare daca nu-l gasesc, altfel actualizez tab-ul
        curent.
    -> NEXT: Parcurg lista pana ajung la ultimul element sau pana intalnesc 
        tab-ul cu ID-ul tab-ului curent. Sar peste santinela in caz ca este
        nevoie. Actualizez tab-ul curent cu cel de dupa.
    -> PREV: Parcurg pana ajung la ultimul element sau pana cand tab-ul urmator
        are ID-ul dorit. Actualizez tab-ul curent cu cel de dinaintea sa.
    -> PAGE_ID: Am parcurs paginile, verificand daca ID-ul coincide. Daca
        gasesc pagina cu ID-ul specificat, creez o copie pentru a o putea 
        atribui ulterior ca pagina curenta. Aloc memorie cu malloc pentru un 
        link nou ce va reprezenta pagina curenta in stiva backward si o 
        introduc. Golesc stiva forward. Actualizez pagina curenta.
    -> BACKWARD: Pastrez intr-o variabila pagina curenta (initiala pag).
        Accesez ultima pagina adaugata in stiva backward (head), o scot din 
        stiva si o fac pagina curenta. Introduc initiala pagina curenta in 
        stiva forward.
    -> FORWARD: Creez un link nou ce va reprezenta pagina curenta. O adaug
        in stiva backward. Scot ultima pagina adaugata in stiva forward
        si o fac pagina curenta.
    -> RECURSIVE_PRINT: Printeaza elementele stivei incepand de la
        primul adaugat. Am ales sa implementez o functie recursiva ca mi se 
        parea cel mai facil mod de a face asta.
    -> PRINT_HISTORY_ID: Parcurg lista, verificand daca exista tab-ul
        cu ID-ul dorit. Daca exista, printez recursiv valorile (de la primul)
        element adaugat din stiva forward. Apoi, printez URL-ul paginii
        curente. Dupa, parcurg backwardStack si printez URL-urile paginilor.
    -> PRINT: Afisez circular ID-urile tuturor taburilor deschise in browser, 
        incepând de la tabul curent, spre dreapta si descrierea paginii 
        curente. Sar peste santinela cand o intampin, trecand la tab 0.

MAIN
    -> Initializez variabilele, deschid fisierele de input si output.
    Creez vectorul de pagini, santinela si tab-ul zero apeland functiile
    specificate mai sus. Actualizez tab-ul curent ca fiind tab 0.
    Citesc nr. de pagini si fiecare pagina in parte. Citesc nr. de comenzi
    si le citesc pe fiecare in parte, eliminand newline-ul de la sfarsit
    citit de functia fgets. Compar input-ul citit cu comenzile posibile
    si apelez functia necesara.

    -> La final, eliberez memoria folosita.
