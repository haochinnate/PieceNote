# Context System with React

- React 16, just about __communication__
- Props System: Gets data from a parent component to a __direct__ child component
- Context System: Gets data from a parent component to __any__ nested child component

## IN and OUT context system

- 建立 context object
  - 2 ways to get information __in__
  - 2 ways to get information __out__

- IN
  1. Default value
  2. 在 parent component 裡面, 建立一個 __Provider__ component
- OUT
  1. this.context
  2. 建立 Consumer component  

## Creating context objects

- 建立 \src\contexts 資料夾
- 在裡面建立 LanguageContext.js

```js
// LanguageContext.js
import React from 'react';

export default React.createContext();

// 如果要設定 default value
export default React.createContext('english');
```

## connect Context object

- 在 child component 中連結 context
- 要建立一個 __contextType__ property

```js
// Button.js
import LanguageContext from '../contexts/LanguageContext';

// "contextType" is special property name
static contextType = LanguageContext;
// 等同於 Button.contextType = LanguageContext;

// 讀取 context
console.log(this.context);
```

## Context Provider (setting context) 

- 在 App component 中, 建立 Provider component

```js
// in App.js
import LanguageContext from '../contexts/LanguageContext';

// 在要使用 context 的 component 地方, 用 該 context 的 provider 包住
// value 是特別的 props name
<LanguageContext.Provider value={this.state.language}>
    <UserCreate />
</LanguageContext.Provider>
```

## flow

1. state 改變
2. 改變 Provider 的 context object
3. 改變 被Provider 包住的 UserCreate
4. Button & Field 因為 context 改變了得到新的值, 也 rerender

- Each separate use of LanguageContext.Provider creates a new __separate pipe__ of information

```js
// 建立 context 物件, 裡面有一個 Provider property
const context = React.createContext('english');

// provider 的 value 會被 assign 到 context object 中
<LanguageContext.Provider value={this.state.language}>
    <UserCreate />
</LanguageContext.Provider>

```

## Context Consumer

```js
// Consumer 裡面要宣告一個 function, 此function 會自動被 Consumer 呼叫
<button className="ui button primary">
    <LanguageContext.Consumer>
        {(value) => value === 'english' ? 'Submit' : 'Voorleggen'}                
    </LanguageContext.Consumer>
</button>
```



- 用 Consumer 可以在單一個 component 中, 使用任一多個 context

## Multiple Contexts

- IN: 再包一層 context

```js
<LanguageContext.Provider value={this.state.language}>
  <ColorContext.Provider value="red">
    <UserCreate />
  </ColorContext.Provider>
</LanguageContext.Provider>
```

- OUT:

```js
<ColorContext.Consumer>
  {(color) =>
    <button className={`ui button ${color}`}>
      <LanguageContext.Consumer>
        {(value) => this.renderSubmit(value)}                
      </LanguageContext.Consumer>
    </button>
  }                
</ColorContext.Consumer>
```

## Context vs Redux

### Redux

- Distributes data to various components
- Centralize data in a store
- Provides mechanism for changing data in the store

### Context

- Distributes data to various components

## use Context in place of Redux

- we need to be able to get data to any component in our hierarchy
- we need to be able to separate our view logic from business logic
- we need to be able to split up business logic

- 建立一個 LanguageStore, 裡面使用 Context 來包住之後要 render 的 chindren 

```js
render() {
  return (
    <Context.Provider value={{ ...this.state, onLanguageChange }}>
      {this.props.children}
    </Context.Provider>
  );
}
```

- 其他地方要取用 language 變成 從object 中取 

```js
{({ language }) => this.renderSubmit(language)}                
     
const text = this.context.language === 'english' ? 'Name' : 'Naam'; 
```

## Context and Redux recap 

### Redux 

- Excellent documentation
- Well-known design patterns
- Tremendous amount of open source libs

### Context

- No need for an extra lib
- Hard to build a 'store' component with cross cutting concerns
