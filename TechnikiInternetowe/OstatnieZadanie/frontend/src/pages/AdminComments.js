import React, { useEffect, useState } from 'react';
import { Container, Button, ListGroup, Row, Col, Form } from 'react-bootstrap';

function AdminComments() {

	const [comments, setComments] = useState([]);
	const [form, setForm] = useState({ content: '', userName: '' });
	const [editingComment, setEditingComment] = useState(null);
	
	const user = JSON.parse(localStorage.getItem('user'));

	useEffect(() => {
		fetch('/admin/comments')
			.then(res => res.json())
			.then(data => setComments(data));
	}, []);

	if (!user || user.role !== 'ADMIN') {
		return <p>Brak dostępu do sesji administratora.</p>;
	}

	async function handleCreate(e) {
		e.preventDefault();
		const res = await fetch('/admin/comments', {
			method: 'POST',
			headers: { 'Content-Type': 'application/json' },
			body: JSON.stringify(form),
		});

		const newCommentRes = await fetch('/admin/comments');
		const newComment = await newCommentRes.json();
		setComments(newComment);
		setForm({ content: '', user: ''});
	}

	async function handleDelete(id) {
		await fetch(`/admin/comments/${id}`, { method: 'DELETE' });
		setComments(comments.filter(u => u.id !== id));
	}

	function startEditing(comment) {
		setEditingComment(comment);
		setForm({ 
			content: comment.content, 
			userName: comment.user.name,  
		});
	}

	async function handleUpdate(e) {
		e.preventDefault();
		const res = await fetch(`/admin/comments/${editingComment.id}`, {
			method: 'PUT',
			headers: { 'Content-Type': 'application/json' },
			body: JSON.stringify(form),

		});

		if (res.ok) {
			const refreshed = await fetch('/admin/comments').then(r => r.json());
			setComments(refreshed);
			setEditingComment(null);
			setForm({ content: '', userName: '' });
		}
		else {
			alert('Błąd aktualizacji');
		}
	}

	return (
		<div
			style={{
				backgroundImage: 'url(/img/admin.jpg)',
               			backgroundSize: 'cover',
               			backgroundPosition: 'center',
               			minHeight: '100vh',
               			padding: '20px',
			}}
		>
			<Container className="my-4">
				<h1 className="mb-4 text-center">Panel administratora</h1>
				
				<Form onSubmit={editingComment ? handleUpdate : handleCreate}>
					<Row className="mb-3">
						<Form.Group as={Col} controlId="formContent">
							<Form.Label className="text-white">Content</Form.Label>
							<Form.Control
								type="text"
								placeholder="Content"
								value={form.content}
								onChange={e => setForm({ ...form, content: e.target.value })}
								required
							/>
						</Form.Group>
						<Form.Group as={Col} controlId="formUserName">
							<Form.Label className="text-white">UserName</Form.Label>
							<Form.Control
								type="text"
								placeholder="UserName"
								value={form.userName}
								onChange={e => setForm({ ...form, userName: e.target.value })}
								required
							/>
						</Form.Group>
					</Row>
					<div className="d-flex gap-2 mb-3">
						<Button type="submit" variant={editingComment ? 'success' : 'primary'}>
							{editingComment ? 'Update' : 'Create'}
						</Button>
						{editingComment && <Button variant="secondary" type="button" onClick={() => {
							setEditingComment(null);
							setForm({ content: '', userName: '' });
						}}>Cancel</Button>}
					</div>
				</Form>

				<ListGroup>
					{comments.map(u => (
						<ListGroup.Item key={u.id} className="d-flex justify-content-between align-itams-center">
							<div>	
								({u.content}) by {u.user.name} 
							</div>
							<div className="d-flex gap-2">
								<Button variant="warning" onClick={() => startEditing(u)}>
									Edit
								</Button>
								<Button variant="danger" onClick={() => handleDelete(u.id)}>
									Delete
								</Button>
							</div>
						</ListGroup.Item>
					))}
				</ListGroup>	

			</Container>
		</div>
	)
		
}

export default AdminComments;	
