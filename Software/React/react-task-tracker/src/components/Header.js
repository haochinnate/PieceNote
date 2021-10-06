import PropTypes from 'prop-types'
import Button from './Button'
import { useLocation } from 'react-router-dom'

// const Header = (props) => {
//     return (
//         <header>
//             <h1>{props.title} Task Tracker</h1>
//         </header>
//     )
// }

const Header = ({title, onAdd, showAdd}) => {
    // const onClick = () => {
    //     console.log('Click')
    // }

    const location = useLocation()

    return (
        <header className='header'>
            {/* <h1 style={{color: 'red', backgroundColor: 'black'}}>{title}..Task Tracker</h1> */}
            {/* <h1 style={headingStyle}>{title}..Task Tracker</h1> */}
            <h1>{title}</h1>
            { location.pathname === "/" && 
                <Button color={showAdd ? 'red' : 'green'} 
                text={showAdd ? 'Close' : 'Add'} 
                onClick={onAdd}/>
            }
            
        </header>
    )
}

// CSS in JS
// const headingStyle = {
//     color: 'green', 
//     backgroundColor: 'black'
// }

Header.defaultProps = {
    title: 'Default Header: ',
}

Header.propTypes = {
    title: PropTypes.string,
    //title: PropTypes.string.isRequired,
}

export default Header
