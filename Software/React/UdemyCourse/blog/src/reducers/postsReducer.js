export default (state = [], action) => {
    // 通常用 switch-case
    switch (action.type) {
        case 'FETCH_POSTS':
            return action.payload;    
        default:
            return state;
    }

    // if (action.type === 'FETCH_POSTS') {
    //     return action.payload;
    // }

    // return state;
};
