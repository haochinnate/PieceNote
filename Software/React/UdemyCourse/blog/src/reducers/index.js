import { combineReducers } from 'redux';
import postsReducer from './postsReducer';
import userReducer from './usersReducer'

export default combineReducers({
    posts: postsReducer,
    users: userReducer
});