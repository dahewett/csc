# process command line arguments
if [ $# -ne 4 ]; then
	echo "Syntax: bash tree_rings.sh number_of_rings tree_height branch_angle branch_factor"
	exit
fi

number_of_rings=$1
tree_height=$2
branch_angle=$3
branch_factor=$4

# generate tree
python generate_tree.py $tree_height $branch_angle $branch_factor > tree.txt
python rotate_scale_translate.py -x 0 -y 250.0 tree.txt > tree0.txt
python rotate_scale_translate.py -f 0.2 tree0.txt > tree1.txt
python rotate_scale_translate.py -x 0 -y -25.0 tree1.txt > tree2.txt

# replicate tree in rings
python rings.py $number_of_rings < tree2.txt > tree_rings.txt
python lines_to_svg.py tree_rings.txt > tree_rings.svg
