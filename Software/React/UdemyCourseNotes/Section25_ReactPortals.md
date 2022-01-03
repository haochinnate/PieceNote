# 

## Modal, 傳統在 html 的實作方式

```html

.modal-body {
    background-color: white;
    margin: auto';
    height: 30%;
    width:30%;
}

.modal {
    height: 100%;
    width: 100%;
    position: fixed;
    background-color: grey;
    left: 0;
    top: 0;
    z-index: 10;
}

<div class="modal">
    <div class="modal-body">
    </div>
</div>
```

```js

```

## Portals

- 藉由 portals, 將 component (modal) 變成 body 底下的 child

```js
// Modal.js
const Modal = (props) => {
    return ReactDOM.createPortal(
        <div className="ui dimmer modals visible active">
            <div className="ui standard modal visible active">
                test modals
            </div>
        </div>,
        document.querySelector('#modal')
    );
};

// index.html
// 將 Modal 綁到 index.html 裡面的某個 component 上
<div id="modal"></div>

// 在 StreamDelete.js 使用 Modal
 <Modal />

```

## 實作 Modal.js

- 參考[Semantic UI doc-Modals-Actions](https://semantic-ui.com/modules/modal.html)

- 點擊 Modal 外圍要離開 Modal

```js
<div onClick={() => history.push('/') } className="ui dimmer modals visible active">
    <div onClick={(e) => e.stopPropagation()} className="ui standard modal visible active">
    // 避免點擊的時候再往上傳, 也離開Modal
    </div>
</div>
```

## React Fragments

```js
// 用 React.Fragments 來取代 div, 在 render 的時候不會產生東西
// 避免用 div 包住時, UI 可能會有非預期的位置偏移
const actions = (
    <React.Fragment>
        <button className="ui button negative">Delete</button>
        <button className="ui button">Cancel</button>
    </React.Fragment>
);

// 也可以用 <> </> 包住
```
