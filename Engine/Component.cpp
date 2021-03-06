#include "Component.h"

void Component::DefineBlockPosition(int row, int column){
    this->row = row;
    this->column = column;

    this->dy = this->GetY(row);
    this->dx = this->GetX(column);
}

void Component::SetRow(int row){
    this->row = row;
    this->dy = (row * BLOCKHEIGHT) + ((BLOCKHEIGHT - this->sh)/2);
}

void Component::SetColumn(int column){
    this->column = column;
    this->dx = (column * BLOCKWIDTH  + HEADERSIZE) + ((BLOCKWIDTH - this->sw)/2);  
}

bool Component::BlockRow(int visitorRow, int visitorColumn){    
    return (visitorColumn == this->column) && (visitorRow == this->row);    
}

bool Component::BlockColumn(int visitorColumn, int visitorRow){
    return (visitorRow == this->row) && (visitorColumn == this->column);    
}

float Component::GetX(int column){
    return (column * BLOCKWIDTH  + HEADERSIZE) + ((BLOCKWIDTH - this->sw)/2);   
}

float Component::GetY(int row){
    return (row * BLOCKHEIGHT) + ((BLOCKHEIGHT - this->sh)/2);
}
