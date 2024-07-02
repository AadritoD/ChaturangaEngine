#pragma once

class Position {
public:

	inline Color side_to_move() const;
	inline Board get_pinned() const;
	inline bool in_check() const;
	inline bool is_legal(const Move&) const;
	inline Board get_occupied() const;
	inline Board get_opponent_occupied() const ;
	template <PieceType> Board get_pieces() const;
	

};