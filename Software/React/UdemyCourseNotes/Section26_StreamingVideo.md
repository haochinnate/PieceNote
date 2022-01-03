# Implementing Streaming Video

#### 重複顯示 component(route)

```js
// path="/streams/new" 
// path="/streams/:id" 

// 在 /streams/new 時 會讓兩個都顯示

// 解決方式: import Switch
import { Router, Route, Switch } from 'react-router-dom';

// 只會選擇 switch 當中 第一個符合的
<Switch>
    <Route />
    <Route />
</Switch>
```

## RTMP server

- [Node-Media-Server](https://github.com/illuspas/Node-Media-Server)

1. \streams\ 底下建立 \rtmpserver 資料夾
2. npm init
3. npm install --save node-medie
4. 建立 index.js
5. script 改成 "start": "node index.js"
6. 執行 npm start 啟動

## OBS installation

- [OBS](obsproject.com)

- Access Live Stream
  - http-flv: http://localhost:8000/live/STREAM_NAME.flv
  - via flv.js over http-flv

## 安裝 flv.js

- [flv.js](https://www.npmjs.com/package/flv.js)

- 在 \client\ 底下

```cmd
npm install --save flv.js
```

- 在 StreamShow 裡面使用, 參考 code

```js
<script src="https://cdn.bootcss.com/flv.js/1.5.0/flv.min.js"></script>
<video id="videoElement"></video>
<script>
    if (flvjs.isSupported()) {
        var videoElement = document.getElementById('videoElement');
        var flvPlayer = flvjs.createPlayer({
            type: 'flv',
            // STREAM_NAME 是在 OBS 中做設定
            url: 'http://localhost:8000/live/STREAM_NAME.flv'
        });
        flvPlayer.attachMediaElement(videoElement);
        flvPlayer.load();
        flvPlayer.play();
    }
</script>
```

## Apply filtering

```js

// 1. 
this.prop.streams.map(stream => {
    if (this.props.currentUserId !== stream.userId) {
        return null;
    }
    return ();
})


// 2. 
this.props.streams.filter(stream => stream.userId === this.props.currentUserId).map(stream => {
    return ();
});

```

## React Final Form

### 安裝

```cmd
npm install final-form react-final-form
```

### reducers/index.js

```js
import { combineReducers } from "redux";
 
import authReducer from "./authReducer";
import streamReducer from "./streamReducer";
 
export default combineReducers({
  auth: authReducer,
  streams: streamReducer,
});
```

### StreamForm.js

```js
import React from "react";
import { Form, Field } from "react-final-form";
 
const StreamForm = (props) => {
  const renderError = ({ error, touched }) => {
    if (touched && error) {
      return (
        <div className="ui error message">
          <div className="header">{error}</div>
        </div>
      );
    }
  };
 
  const renderInput = ({ input, label, meta }) => {
    const className = `field ${meta.error && meta.touched ? "error" : ""}`;
    return (
      <div className={className}>
        <label>{label}</label>
        <input {...input} autoComplete="off" />
        {renderError(meta)}
      </div>
    );
  };
 
  const onSubmit = (formValues) => {
    props.onSubmit(formValues);
  };
 
  return (
    <Form
      initialValues={props.initialValues}
      onSubmit={onSubmit}
      validate={(formValues) => {
        const errors = {};
 
        if (!formValues.title) {
          errors.title = "You must enter a title";
        }
 
        if (!formValues.description) {
          errors.description = "You must enter a description";
        }
 
        return errors;
      }}
      render={({ handleSubmit }) => (
        <form onSubmit={handleSubmit} className="ui form error">
          <Field name="title" component={renderInput} label="Enter Title" />
          <Field
            name="description"
            component={renderInput}
            label="Enter Description"
          />
          <button className="ui button primary">Submit</button>
        </form>
      )}
    />
  );
};
 
export default StreamForm;
```