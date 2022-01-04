import React from 'react';
import Link from './Link';

const Header = () => {
    return (
        <div className="ui secondary pointing menu">
            <Link href="/jsx" className="item">
                1. JSX example
            </Link>
            <Link href="/components" className="item">
                2. components
            </Link>
            <Link href="/seasons" className="item">
                3. seasons
            </Link>
            
        </div>
    );
};

export default Header;
