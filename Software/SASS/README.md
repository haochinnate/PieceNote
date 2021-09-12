
- [官網](https://sass-lang.com/guide)

- Visual Studio Extensions: Live Sass Compiler

- 按下 "Wach Sass" 就會產生 style.css


## variable - start with $

### 宣告變數

```scss
$primaryBtn : rgb(56, 146, 142);
```

### 先前可能是

```css
header button {
    background: red;
}

.contact button {
    background: red;
}
```

### 使用變數

```scss
header button {
    background: $primaryBtn;
}

.contact button {
    background: $primaryBtn;
}
```


## Nesting

```scss
header {
    button {
        background: $primaryBtn;
        &:hover {
            background: red;
        }
        &::after {
            background: green;
            content: 'Helllooooo';
        }
    }
}
```

等同於

```css
header button {
    background: rgb(56, 146, 142);
}
```

## Modules

- 名稱為底線開頭, ex: _header.scss

- 使用, 用@use, @import 有一些缺點, 官網有說明

```scss
@use './header';
```

## Mixins

- 像 javascript function 

- 宣告

```scss
@mixin flexCenter {
    display: flex;
    justify-content: center;
    align-items: center;
}
```

- 使用

```scss
header {
    @include flexCenter();
}
```

- 加參數

```scss
@mixin flexCenter($direction) {
    flex-direction: $direction;
}

header {
    @include flexCenter(column);
}
```

## Extend/Inheritance

- 繼承

```scss
@extend header;
```

## Calculation 

```scss
{
    width: 100% - 20%;
}
```

## %: placeholder selector

- [官網解說](https://sass-lang.com/documentation/style-rules/placeholder-selectors)

