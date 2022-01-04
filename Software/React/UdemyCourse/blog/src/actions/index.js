import _ from 'lodash';
import jsonPlaceholder from "../apis/jsonPlaceholder";

// // this is BAD approach
// export const fetchPosts = async () => {
//     const response = await jsonPlaceholder.get('/posts');
    
//     // const promise = jsonPlaceholder.get('/posts');
    
//     return {
//         type: 'FETCH_POSTS',
//         payload: response
//     };
// };

export const fetchPostsAndUsers = () => async (dispatch, getState) => {
    // 1. call 'fetchPosts'
    // console.log('start to fetchposts');
    await dispatch(fetchPosts());
    // console.log('end of fetchposts');

    // 2. Get lists of posts
    // 3. Find all unique userId's from list of posts
    // console.log(getState().posts);
    const userIds = _.uniq(_.map(getState().posts, 'userId'));
    // console.log(userIds)


    // 4. iterate over unique userId's
    // 5. call 'fetchUser' with each userId
    userIds.forEach(id => dispatch(fetchUser(id)));

    // Promise.all(userIds.map(id => dispatch(fetchUser(id))))

    // 也可以寫成下面這樣
    // _.chain(getState().posts)
    //     .map('userId')
    //     .uniq()
    //     .forEach(id => dispatch(fetchUser(id)))
    //     .value();
};

export const fetchPosts = () => async dispatch => {
    const response = await jsonPlaceholder.get('/posts');

    dispatch({ type: 'FETCH_POSTS', payload: response.data });
};


export const fetchUser = (id) => async dispatch => {
    const response = await jsonPlaceholder.get(`/users/${id}`);

    dispatch({ type: 'FETCH_USER', payload: response.data });
};


// use lodash memoize function to avoid duplicate fetch user
// export const fetchUser = (id) => dispatch => {
//     _fetchUser(id, dispatch);
// };

// const _fetchUser = _.memoize(async (id, dispatch) => {
//     const response = await jsonPlaceholder.get(`/users/${id}`);

//     dispatch({ type: 'FETCH_USER', payload: response.data });
// });