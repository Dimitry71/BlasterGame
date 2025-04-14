# Blaster Game (Unreal Engine 5)

Blaster Game — це 3D-гра, розроблена на Unreal Engine 5. Проєкт має адаптивний UI, підтримує пакування для Windows та інших платформ. Цей репозиторій містить код, ресурси, документацію для розробників та інструкції для розгортання.

## 📦 Вміст репозиторію

- `BlasterGame/` — основний код проєкту UE5
- `docs/` — документація (deployment, update, backup, scripts)
- `Saved/`, `Intermediate/` — автоматично створювані UE5 директорії (ігноруються в Git)

## 🧰 Необхідні інструменти

Перед початком роботи, переконайтесь, що у вас встановлені наступні компоненти:

- [Unreal Engine 5.3+](https://www.unrealengine.com/)
- [JetBrains Rider з Unreal плагіном](https://www.jetbrains.com/rider/)
- Git
- Visual Studio 2022 (із компонентами C++ та Game Development)
- CMake (опціонально, для кастомних збірок)

## 🚀 Як запустити проєкт (розробнику)

1. **Клонувати репозиторій**
    ```bash
    git clone https://gitlab.com/your-username/blaster-game.git
    cd blaster-game
    ```

2. **Відкрити проєкт у Rider або UE5 Editor**
    - Відкрий `BlasterGame.uproject` у Unreal Editor
    - Або імпортуй у JetBrains Rider

3. **Побудувати проєкт**
    - Через UE5: `File → Generate Visual Studio project files`, далі `Build`
    - Через Rider: `Build → Build Solution`

4. **Запустити гру**
    - В Editor: натисни `Play`
    - Для окремого вікна: `Play → Standalone Game`

## 🛠 Базові команди

- **Очищення тимчасових файлів:**
    ```bash
    ./docs/scripts/clean-temp.sh
    ```
- **Збірка гри:**
    ```bash
    ./docs/scripts/build-project.sh
    ```

## 🗃 Структура проєкту

- `Content/` — візуальні/аудіо ресурси
- `Source/` — C++ код
- `Config/` — налаштування проєкту
- `Docs/` — технічна документація
- `.uproject` — файл конфігурації Unreal Engine

## 📄 Ліцензія

Проєкт створено в рамках бакалаврської роботи. Ліцензія — навчальна/університетська. Усі права захищено.
