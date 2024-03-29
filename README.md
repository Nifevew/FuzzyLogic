# Система нечетких множеств (Нечеткая логика)

### Описание примера 

Опишем два нечетких множества (допустим, известно как зависит здоровье человека, от его роста):
```
A = очень высокий = { 0/150  0.3/170  0.5/180  0.7/190  1/200 }
B = здоровый = { 0.4/150  0.9/170  1/180  0.7/190  0.2/200 }
```

Тогда определив дополнение множества `A`, как `A'` и, назвав его `"средний" [рост]`, можно получить множества `B'` - `"более-менее" [здоровый]`. 
```
A' = средний = { 0.3/150  0.8/170  1/180  0.7/190  0.5/200 }
```

Предположим, что существует некоторая зависимость `A → B`, тогда на основе композиционного правила, можно получить множество `B'`.
```
B' = более–менее = { 0.4/150  0.7/170  0.7/180  0.7/190  0.2/200 }
```

Это можно интерпретировать как:
```
- Если при росте 150см человек на 0% очень высокий и на 40% здоровый и при этом средний рост 30%, то он более-менее здоровый на 40%.
- Если при росте 170см человек на 30% очень высокий и на 90% здоровый и при этом средний рост 80%, то он более-менее здоровый на 70%.
- Если при росте 180см человек на 50% очень высокий и на 100% здоровый и при этом средний рост 100%, то он более-менее здоровый на 70%.
- Если при росте 190см человек на 70% очень высокий и на 70% здоровый и при этом средний рост 70%, то он более-менее здоровый на 70%.
- Если при росте 200см человек на 100% очень высокий и на 20% здоровый и при этом средний рост 50%, то он более-менее здоровый на 20%.
```

На основе множеств A и B применим правило Modus Ponens: `B' = A' ∘ R = A' ∘ (A → B)`  
Отсюда получим значение `0.7`, которое можно интерпретировать следующим образом: `Если человек средний и существует правило, что очень высокий -> здоровый, то тогда он более-менее здоровый на 70%`.

### Сборка примера

```
> mkdir build 
> cd build 
> cmake ../ -DBOOST_DIR=<PATH_TO_BOOST_ROOT> 
> cmake --build . --target FuzzyLogic --config <Debug or Release>
> .\<YOUR_CONFIG_NAME>\FuzzyLogic.exe
```