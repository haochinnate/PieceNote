import React, { useState } from 'react'

const Accordion = ({ items }) => {
    const [activeIndex, setActiveIndex] = useState(null);

    // helper function 
    const onTitleClick = (index) => {
        // console.log('Title clicked', index)
        setActiveIndex(index);
    };

    const renderItems = items.map((item, index) => {
        const active = index === activeIndex ? 'active' : 'string';


        return (
            // 如果是用 <div> 包住的話會有兩個 border
            // 所以改用 React.Fragment
            <React.Fragment key={item.title}>
                <div className={`title ${active}`}
                    onClick={() => onTitleClick(index)}>
                    <i className="dropdown icon"></i>
                    {item.title}
                </div>
                <div className={`content ${active}`}>
                    <p>{item.content}</p>
                </div>
            </React.Fragment>
        )
    });
    
    return (
        <div className="ui styled accordion">
            {renderItems}
            {/* <h1>{activeIndex}</h1> */}
        </div>
    )
};

export default Accordion;
