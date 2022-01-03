# Navigation

- 通常都是用 __React-Router__
- 這個章節先自己做

#### Mapping

- 在 browser 裡面打 window.location 可以有一些資訊
- pathname 是 domain 和 port 後的所有東西 ex: /translate
  - / -> Accordion
  - /list -> Search
  - /dropdown -> Dropdown
  - /translate -> Translate

```js
const showAccordion = () => {
  if (window.location.pathname === '/') {
    return <Accordion items={items}/>
  }
}

return (
  <div>
    {showAccordion()}
  </div>
)
// 其他以此類推
```

#### 改進, 建立 reusable route component 

- 這個 component 會根據 path name 來決定要 show 什麼component

```js
const Route = ({ path, children }) => {
    return (
        window.location.pathname === path
        ? children 
        : null
    );
};

<Route path="/" >
    <Accordion items={items} />
</Route>
```

#### 處理 Naviation

1. user click on something

2. 改變 URL, 但是不要整個page 都 refresh

```js
// 可以改URL, 但是 content 不會變
// window.history.pushState({}, '', '/list')

const Link = ({ className, href, children }) => {
    const onClick = (event) => {
        event.preventDefault();
        window.history.pushState({}, '', href);
    };
    
    return (
        <a onClick={onClick} className={className} href={href}>
            {children}
        </a>
    );
};
```


3. Each Route could detect the URL has changed
  - Navigation Event
  - 送到所有 Route component, 告訴他們 URL 改了

```js
// in Link.js
// navigation event, told other components URL had changed
const navEvent = new PopStateEvent('popstate');
window.dispatchEvent(navEvent);

// in Route.js
useEffect(() => {
    const onLocationChange = () => {
        console.log('Location Change');
    };

    window.addEventListener('popstate', onLocationChange);

    return () => {
        window.removeEventListener('popstate', onLocationChange);
    };
}, [])

```

4. Route could update piece of state tracking the current pathname

```js
const [currentPath, setCurrentPath] = useState(window.location.pathname);

const onLocationChange = () => {
    // update the path
    setCurrentPath(window.location.pathname);
};

return (currentPath === path ? children : null);
```


5. Each Route rerenders, showing/hiding components appropriately


#### 處理在新分頁開啟

- 按 Ctrl/Command 在新分頁開啟
```js
const onClick = (event) => {
    if (event.metaKey || event.ctrlKey) {
        return;
    }
}
```

#### refactor 

```js

onVideoSelect={(video) => {setSelectedVideo(video)}} />
// 等同於
onVideoSelect={setSelectedVideo} />


```