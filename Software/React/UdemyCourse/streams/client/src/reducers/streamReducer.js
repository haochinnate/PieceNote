import _ from 'lodash';
import {
    CREATE_STREAM,
    FETCH_STREAMS,
    FETCH_STREAM,
    EDIT_STREAM,
    DELETE_STREAM
} from '../actions/types';


const streamReducer = (state = {}, action) => {
    switch (action.type) {
        case CREATE_STREAM:
            return { ...state, [action.payload.id]: action.payload };
        
        case FETCH_STREAM:
            return { ...state, [action.payload.id]: action.payload };

        case FETCH_STREAMS:
            return { ...state, ..._.mapKeys(action.payload, 'id') };

        case EDIT_STREAM:
            return { ...state, [action.payload.id]: action.payload };
        
        case DELETE_STREAM:
            // return { ...state, [action.payload]: undefined };
            return _.omit(state, action.payload);     

        default:
            return state;
    }
};

export default streamReducer;