# LayersSFML

Prosty projekt C++ z SFML do nauki systemu warstw i pracy w Visual Studio, który można edytować w domu i w szkole bez przenoszenia plików ręcznie. Dzięki Git + GitHub wszystkie zmiany są zsynchronizowane.

---

## Jak to działa

Git + GitHub działa jak "magiczny pendrive w chmurze":

- `git add .` – dodajesz zmiany do śledzenia przez Git
- `git commit -m "opis zmian"` – zapisujesz zmiany lokalnie
- `git push` – wysyłasz zmiany na GitHub
- `git pull` – pobierasz zmiany z GitHub i scala z tym, co masz lokalnie

---

## Workflow

### 1. Praca w domu
1. Otwórz projekt w Visual Studio
2. Edytuj kod (np. `src/main.cpp` lub dodawaj klasy)
3. Kiedy skończysz:
    ```bash
    git status
    git add .
    git commit -m "opis zmian"
    git push
    ```

### 2. Praca w szkole
1. Na szkolnym komputerze:
    ```bash
    git clone https://github.com/TWOJA_NAZWA/LayersSFML.git
    ```
    Lub jeśli już masz projekt:
    ```bash
    git pull
    ```
2. Edytujesz kod w VS
3. Po skończeniu pracy:
    ```bash
    git add .
    git commit -m "opis zmian"
    git push
    ```

### 3. Powrót do domu
```bash
git pull
